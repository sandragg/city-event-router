#ifndef ROUTING_STRTG_BASE
#define ROUTING_STRTG_BASE


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

inline time_t predict(time_t now, std::unordered_set<int>& unvisited, int point_id)
{
	return now;
};

inline time_t calculate_start_time(int point_id, time_t& now)
{
	return now;
};


#endif //ROUTING_STRTG_BASE
