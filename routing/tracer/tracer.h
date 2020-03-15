#ifndef ROUTING_TRACER_H
#define ROUTING_TRACER_H

#include <vector>
#include <queue>
#include <map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <ctime>
#include "../timetable/timetable.h"
#include "../distance-matrix/distance-matrix.h"


namespace tracer
{

using namespace std;

using heuristic = time_t(*)(time_t now, unordered_set<int>&, int next_vertex);
using end_condition = bool(*)(time_t now, unordered_set<int>&);

struct RoutePoint
{
	int id;
	timetable::Interval time; // start time and duration
};

struct PriorityPoint
{
	int id;
	time_t priority;

	bool operator>(const PriorityPoint& rhs)
	{
		return this->priority > rhs.priority;
	}
};

template<typename End_Cond_Tp, typename Heuristic_Tp>
vector<RoutePoint> traceGraph(DistanceMatrix& dist_matrix, End_Cond_Tp&& is_end, Heuristic_Tp&& predict);

#include "tracer.cpp"

} // namespace tracer


#endif //ROUTING_TRACER_H
