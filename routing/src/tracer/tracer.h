#ifndef ROUTING_TRACER_H
#define ROUTING_TRACER_H

#include <unordered_set>
#include <iostream>
#include <ctime>
#include "../timetable/timetable.h"
#include "../distance-matrix/distance-matrix.h"
#include "../tree/list-of-siblings/list-of-siblings.h"

/**
 * Includes general tracer logic, utils, input and output models.
 */
namespace tracer
{

/**
 * Heuristic function.
 * Function is used in #traceGraph to compute the priority of a point with a *point_id*.
 *
 * @param now Current time
 * @param unvisited Unvisited points ids
 * @param point_id Next point to visit
 * @return Time priority of a point with a *point_id*
 */
using heuristic = time_t(*)(time_t now, std::unordered_set<int>& unvisited, int point_id);
/**
 * Trace end check function.
 * Function is used in #traceGraph to check trace end, e.g. time is up, improper route and so on.
 *
 * @param now Current time
 * @param unvisited Unvisited points ids
 * @return If tracing should be stopped - **true**, otherwise - **false**.
 */
using end_condition = bool(*)(time_t now, std::unordered_set<int>& unvisited);
/**
 * Return start time at the point regarding to current time.
 * Current time can be increased on a duration time in this point.
 *
 * @param point_id Current point
 * @param now Current time
 * @return 	Start time at the point with *point_id* in accordance with external constraints,
 * 			such as time before open.
 */
using start_time_calculator = time_t(*)(int point_id, time_t& now);

struct RoutePoint
{
	/**
	 * %Point id
	 */
	int id;
	/**
	 * Time data.
	 * Where
	 *  - #time[start] - start time;
	 *  - #time[end] - duration.
	 *
	 * @see #timetable::Interval
	 */
	timetable::Interval time;

	bool operator==(const RoutePoint &rhs) const;
};

/**
 * Tracing function.
 * All points in *dist_matrix* are considered as a **complete weighted graph G(V,E)**
 * where **V** - a set of vertices, **E** - a set of edges.
 * Each pair of vertices **Vi & Vj** has an edge **E{i,j}** with weight *dist_matrix[i][j]*.
 *
 * @tparam End_Cond_Tp #end_condition
 * @tparam Heuristic_Tp #heuristic
 * @param dist_matrix Distance matrix
 * @param is_end Trace end check function
 * @param predict %Point priority computation function
 * @return Array of route points
 */
template<typename End_Cond_Tp, typename Heuristic_Tp, typename Time_Calculator_Tp>
list_of_siblings::Tree<RoutePoint> traceGraph(
	DistanceMatrix& dist_matrix,
	End_Cond_Tp&& is_end,
	Heuristic_Tp&& predict,
	Time_Calculator_Tp&& calc_start_time);

} // namespace tracer


#endif //ROUTING_TRACER_H
