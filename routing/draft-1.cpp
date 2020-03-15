#include<limits>
#include "route-context/route-context.h"


auto is_end(route_context::RouteContext& ctx) {
	return [&](time_t now, std::unordered_set<int>& unvisited) -> bool
	{
		ctx.UpdateOnNewTick(now);
		return unvisited.empty() || ctx.UpcomingTime() < now;
	};
};

auto predict(route_context::RouteContext& ctx) {
	return [&](time_t now, std::unordered_set<int>& unvisited, int point_id) -> time_t
	{
		time_t result = 0;

		if (!ctx.IsPointOpen(point_id))
		{
			auto time_before_open = ctx.TimeBeforePointOpen(point_id);

			if (!time_before_open)
				return std::numeric_limits<time_t>::max();

			result += time_before_open * ctx.TimeBeforeOpenFee();
		}
		auto upcoming_time = ctx.UpcomingTime() - now;
		auto upcoming_point_id = ctx.UpcomingPointId();

		if (point_id != upcoming_point_id)
		{
			auto dist_to_upcoming = ctx.DistanceMatrix()[point_id][upcoming_point_id];
			result += ctx.MinStayTime() + dist_to_upcoming;
		}

		if (result <= upcoming_time)
			return upcoming_time - result;

		auto late_fee = (result - upcoming_time) * ctx.LateFee();
		return result + late_fee;
	};
};
