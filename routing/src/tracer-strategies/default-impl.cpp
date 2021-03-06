#include "../tracer/tracer.cpp"

#include <type_traits>
#include "default.h"


using End_Cond = std::invoke_result<decltype(is_end), route_context::RouteContext&>::type;
using Heuristic = std::invoke_result<decltype(predict), route_context::RouteContext&>::type;
using Time_Calculator = std::invoke_result<decltype(calculate_start_time), route_context::RouteContext&>::type;

template list_of_siblings::Tree<tracer::RoutePoint<int>>
tracer::trace_graph(
	DistanceMatrix& dist_matrix,
	End_Cond&& is_end,
	Heuristic&& predict,
	Time_Calculator&& calc_start_time);