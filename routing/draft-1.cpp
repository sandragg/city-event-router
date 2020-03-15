#include "route-context/route-context.h"


auto is_end(route_context::RouteContext& ctx) {
	return [&](time_t now, std::unordered_set<int>& unvisited) -> bool
	{
		return unvisited.empty();
	};
};

auto predict(route_context::RouteContext& ctx) {
	return [&](time_t now, std::unordered_set<int>& unvisited, int next_vertex) -> time_t
	{
		return (time_t)0;
	};
};
