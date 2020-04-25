#include "tracer.cpp"

#include <type_traits>
#include "../draft-1.h"


using End_Cond = std::invoke_result<decltype(is_end), route_context::RouteContext&>::type;
using Heuristic = std::invoke_result<decltype(predict), route_context::RouteContext&>::type;

template list_of_siblings::Tree<tracer::RoutePoint>
tracer::traceGraph(
	DistanceMatrix& dist_matrix,
	End_Cond&& is_end,
	Heuristic&& predict);