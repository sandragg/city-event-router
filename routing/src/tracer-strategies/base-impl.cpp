#include "../tracer/tracer.cpp"

#include <type_traits>
#include "base.h"


template class tracer::Route<std::string>;
template class tracer::Route<tracer::RoutePoint>;

using End_Cond = std::invoke_result<decltype(is_end), route_context::RouteContext&>::type;
using Heuristic = decltype(predict);
using Time_Calculator = decltype(calculate_start_time);

template list_of_siblings::Tree<tracer::RoutePoint>
tracer::trace_graph(
	DistanceMatrix& dist_matrix,
	End_Cond&& is_end,
	Heuristic& predict,
	Time_Calculator& calc_start_time);

template std::vector<tracer::Route<std::string>>
tracer::find_matched_routes(const list_of_siblings::Tree<std::string> &tree, size_t limit);

template std::vector<tracer::Route<tracer::RoutePoint>>
tracer::find_matched_routes(const list_of_siblings::Tree<tracer::RoutePoint> &tree, size_t limit);