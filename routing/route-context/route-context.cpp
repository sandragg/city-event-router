#include <map>
#include "route-context.h"
using namespace route_context;


RouteContext::RouteContext(
	const class DistanceMatrix& dist_matrix,
	const std::vector<Waypoint>& points,
	const CustomSettings& settings)
{
	this->dist_matrix = &dist_matrix;

	this->min_stay_time = settings.min_stay_time;
	this->late_fee = settings.late_fee;
	this->time_before_open_fee = settings.time_before_open_fee;
	this->extra_time_fee = settings.extra_time_fee;
	this->time_range = settings.time_range;

	std::map<time_t, int> closing_time_to_point_id;
	for (auto& point : points)
		closing_time_to_point_id.emplace(ComputePointClosingTime(point), point.id);

	std::unordered_map<int, int> point_id_to_priority;
	for (const auto &point : *settings.points_priorities)
		point_id_to_priority.emplace(point.id, point.priority);

	pointIdToIndex.reserve(points.size());
	time_priorities.reserve(points.size());
	priorities.reserve(points.size());

	int index = 0;
	for (auto &[time, id] : closing_time_to_point_id)
	{
		pointIdToIndex.emplace(id, index);
		time_priorities[index] = time;
		priorities[index] = point_id_to_priority.at(id);
		index++;
	}

	this->points = points;
	std::sort(
		this->points.begin(),
		this->points.end(),
		[this](const Waypoint& lhs, const Waypoint& rhs)
		{
			return pointIdToIndex.at(lhs.id) < pointIdToIndex.at(rhs.id);
		});
}

void RouteContext::UpdateOnNewTick(time_t now)
{
	while (upcoming < time_priorities.size())
		if (time_priorities[upcoming++] >= now) return;

	upcoming = RouteContext::PAST_TIME;
}

int RouteContext::PointPriority(int point_id) const
{
	return priorities[pointIdToIndex.at(point_id)];
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

bool RouteContext::PastTime() const
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

bool RouteContext::IsPointOpen(time_t now, int point_id) const
{
	auto immediate_interval = points[pointIdToIndex.at(point_id)]
		.schedule
		.GetImmediate(now);
	return immediate_interval ? now >= immediate_interval->start : false;
}

time_t RouteContext::TimeBeforePointOpen(time_t now, int point_id) const
{
	auto immediate_interval = points[pointIdToIndex.at(point_id)]
		.schedule
		.GetImmediate(now);

	if (!immediate_interval) return RouteContext::PAST_TIME;

	auto difference = immediate_interval->start - now;
	return difference > 0 ? difference : 0;
}
