#include "route-context.h"

#include <map>
#include <queue>
#include <algorithm>


namespace route_context
{

RouteContext::RouteContext(
	const class DistanceMatrix& dist_matrix,
	const std::vector<Waypoint>& waypoints)
{
	this->dist_matrix = &dist_matrix;

	this->min_stay_time = 1;
	this->late_fee = 1;
	this->time_before_open_fee = 1;
	this->extra_time_fee = 1;
	this->time_range = nullptr;
	this->priorities = nullptr;

	BaseInitialization(waypoints);
}

RouteContext::RouteContext(
	const class DistanceMatrix& dist_matrix,
	const std::vector<Waypoint>& waypoints,
	const CustomSettings& settings)
{
	this->dist_matrix = &dist_matrix;

	this->min_stay_time = settings.min_stay_time;
	this->late_fee = settings.late_fee;
	this->time_before_open_fee = settings.time_before_open_fee;
	this->extra_time_fee = settings.extra_time_fee;
	this->time_range = settings.time_range
		? new timetable::Interval(*settings.time_range)
		: nullptr;

	BaseInitialization(waypoints);

	if (!settings.points_priorities)
	{
		this->priorities = nullptr;
		return;
	}

	this->priorities = new std::vector<int>(waypoints.size());

	for (auto &point : *settings.points_priorities)
		(*this->priorities)[point_id_to_index.at(point.id)] = point.priority;
}

RouteContext::~RouteContext()
{
	delete this->time_range;
	delete this->priorities;
}

void RouteContext::UpdateOnNewTick(time_t now)
{
	if (upcoming == RouteContext::PAST_TIME)
		upcoming = time_priorities.size() - 1;

	if (time_priorities[upcoming] > now)
	{
		for (upcoming--; upcoming >= 0; upcoming--)
		{
			if (time_priorities[upcoming] < now)
			{
				upcoming++;
				return;
			}
		}
		upcoming = 0;
		return;
	}

	for (; upcoming < time_priorities.size(); upcoming++)
		if (time_priorities[upcoming] >= now) return;

	upcoming = RouteContext::PAST_TIME;
}

void RouteContext::SkipUpcomingPoint()
{
	if (upcoming == time_priorities.size() - 1)
		upcoming = RouteContext::PAST_TIME;
	else
		upcoming++;
}

int RouteContext::PointPriority(int point_id) const
{
	auto index = point_id_to_index.at(point_id);
	return priorities ? (*priorities)[index] : 1;
}

const DistanceMatrix& RouteContext::DistanceMatrix() const
{
	return *dist_matrix;
}

bool RouteContext::UpcomingExists() const
{
	return upcoming != RouteContext::PAST_TIME;
}

time_t RouteContext::UpcomingTime() const
{
	return time_priorities[upcoming];
}

int RouteContext::UpcomingPointId() const
{
	return points[upcoming].id;
}

int RouteContext::PastTime() const
{
	return RouteContext::PAST_TIME;
}

time_t RouteContext::LateFee() const
{
	return late_fee;
}

time_t RouteContext::TimeBeforeOpenFee() const
{
	return time_before_open_fee;
}

time_t RouteContext::ExtraTimeFee() const
{
	return extra_time_fee;
}

time_t RouteContext::MinStayTime() const
{
	return min_stay_time;
}

const timetable::Interval* RouteContext::TimeRange() const
{
	return time_range;
}

bool RouteContext::IsPointOpen(time_t now, int point_id) const
{
	auto immediate_interval = points[point_id_to_index.at(point_id)]
		.schedule
		.GetImmediate(now);
	return immediate_interval ? now >= immediate_interval->start : false;
}

time_t RouteContext::TimeBeforePointOpen(time_t now, int point_id) const
{
	auto immediate_interval = points[point_id_to_index.at(point_id)]
		.schedule
		.GetImmediate(now);

	if (!immediate_interval) return RouteContext::PAST_TIME;

	auto difference = immediate_interval->start - now;
	return difference > 0 ? difference : 0;
}

time_t RouteContext::ComputePointClosingTime(const Waypoint& point) const
{
	auto schedule = this->time_range
		? point.schedule.GetInInterval(*this->time_range, true)
		: point.schedule.GetAll();

	time_t last_time = RouteContext::PAST_TIME;
	time_t temp_time = 0;
	for (auto &interval : schedule)
	{
		temp_time = interval.end - this->min_stay_time;
		if (temp_time >= interval.start)
			last_time = temp_time;
	}

	return last_time;
}

void RouteContext::BaseInitialization(const std::vector<Waypoint>& waypoints)
{
	std::multimap<time_t, int> closing_time_to_point_id;
	for (auto& point : waypoints)
		closing_time_to_point_id.emplace(ComputePointClosingTime(point), point.id);

	point_id_to_index.reserve(waypoints.size());
	time_priorities.resize(waypoints.size());

	int index = 0;
	for (auto &[time, id] : closing_time_to_point_id)
	{
		point_id_to_index.emplace(id, index);
		time_priorities[index] = time;
		index++;
	}

	this->upcoming = 0;
	this->points = waypoints;

	std::sort(
		this->points.begin(),
		this->points.end(),
		[this](const Waypoint& lhs, const Waypoint& rhs)
		{
			return point_id_to_index.at(lhs.id) < point_id_to_index.at(rhs.id);
		});
}

} // namespace route_context
