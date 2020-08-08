#ifndef ROUTING_STRTG_DEFAULT
#define ROUTING_STRTG_DEFAULT

#include <unordered_set>
#include <limits>
#include "../route-context/route-context.h"


inline auto is_end(route_context::RouteContext& ctx) {
	return [&](time_t now, std::unordered_set<int>& unvisited) -> bool
	{
		ctx.UpdateOnNewTick(now);

		/* Skip visited points */
		while (ctx.UpcomingExists() && !unvisited.count(ctx.UpcomingPointId()))
			ctx.SkipUpcomingPoint();

		return unvisited.empty() || !ctx.UpcomingExists();
	};
};

inline auto predict(route_context::RouteContext& ctx) {
	return [&](time_t now, std::unordered_set<int>& unvisited, int point_id) -> time_t
	{
		time_t result = 0;

		if (!ctx.IsPointOpen(now, point_id))
		{
			auto time_before_open = ctx.TimeBeforePointOpen(now, point_id);

			if (time_before_open == ctx.PastTime())
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

		/* Will be late for the upcoming point */
		if (result > upcoming_time)
		{
			auto late_fee = (result - upcoming_time) * ctx.LateFee();
			return result + late_fee;
		}

		/* Will be at the latest available time at the upcoming point  */
		if (result == upcoming_time)
			return upcoming_time - result;

		/* Will be on time or earlier at the upcoming point */
		auto time_before_open = ctx.TimeBeforePointOpen(now, upcoming_point_id) - now;
		/* If it's earlier than point opening */
		if (time_before_open > 0)
		{
			auto extra_fee = (time_before_open - result) * ctx.ExtraTimeFee();
			result -= extra_fee;
		}

		return upcoming_time - result;
	};
};

inline auto calculate_start_time(route_context::RouteContext& ctx)
{
	return [&](int point_id, time_t& now) -> time_t
	{
		auto start_time = now + ctx.TimeBeforePointOpen(now, point_id);
		now += ctx.MinStayTime();
		return start_time;
	};
};


#endif // ROUTING_STRTG_DEFAULT
