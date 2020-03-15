#ifndef ROUTING_ROUTE_CONTEXT_H
#define ROUTING_ROUTE_CONTEXT_H

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <vector>
#include "../distance-matrix/distance-matrix.h"
#include "../timetable/timetable.h"

namespace route_context
{

using namespace std;
using namespace timetable;

class RouteContext
{
	public:
		RouteContext() {}
		void UpdateOnNewTick(time_t now);

		/*
		 * User preferences
		 */
		DistanceMatrix *dist_matrix;

		void *points; // TODO declare way point type

		/* Point id -> priority */
		unordered_map<int, int> priorities;

		time_t min_stay_time;

		/* Coefficients ans fees */
		time_t late_fee;
		time_t time_before_open_fee;
		time_t extra_time_fee;

		/* Available time interval for route */
		Interval time_range;

		/*
		 * Payload for tracer
		 */
		/* Sorted vector of points closing time */
		vector<time_t> time_priorities;

		/* Point id -> index in time_priorities */
		unordered_map<int, int> pointIdToIndex;

		/* Iterator to the nearest closing point in time_priorities */
		vector<time_t>::iterator upcoming;
};

} // namespace route_context

#endif //ROUTING_ROUTE_CONTEXT_H
