#include "route-context.h"
using namespace route_context;


void RouteContext::UpdateOnNewTick(time_t now)
{
	upcoming = lower_bound(upcoming, time_priorities.end(), now);
}

int RouteContext::PointPriority(int point_id) const
{
	return priorities.at(point_id);
}

const DistanceMatrix& RouteContext::DistanceMatrix() const
{
	return *dist_matrix;
}

time_t RouteContext::UpcomingTime() const
{
	return upcoming == time_priorities.end() ? -1 : *upcoming; // mmm..magic numbers :P
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
