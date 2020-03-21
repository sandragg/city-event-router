#include "route-context.h"
using namespace route_context;


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
