#include "route-context/route-context.h"


auto is_end(route_context::RouteContext& ctx) {
	return [&](time_t now, std::unordered_set<int>& unvisited) -> bool
	{
		ctx.UpdateOnNewTick(now);
		return unvisited.empty() || now >= ctx.time_range.end;
	};
};

auto predict(route_context::RouteContext& ctx) {
	return [&](time_t now, std::unordered_set<int>& unvisited, int next_point_id) -> time_t
	{
		return 0;
	};
};
