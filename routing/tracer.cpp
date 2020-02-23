#include <vector>
#include <queue>
#include <map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <ctime>
#include "timetable/timetable.h"
#include "distance-matrix/distance-matrix.h"

namespace tracer
{

using namespace std;

struct RoutePoint
{
	int id;
	timetable::Interval time;
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

using heuristic = time_t(*)(time_t now, unordered_set<int>, int next_vertex);
using end_condition = bool (*)(time_t now, unordered_set<int>);

vector<RoutePoint> traceGraph(DistanceMatrix& dist_matrix, end_condition is_end, heuristic predict)
{
	auto matrix_size = dist_matrix.Size();
	vector<RoutePoint> route;

	int point = 0;
	unordered_set<int> unvisited;
	for (int i = 1; i < matrix_size; i++)
		unvisited.insert(i);

	time_t curr_time = 0;
	// mb priority queue will help to go back step by step in case of false route.
	priority_queue<
		PriorityPoint,
		vector<PriorityPoint>,
		greater<>
	> next_step;

	while (!is_end(curr_time, unvisited))
	{
		for (auto& id : unvisited)
		{
			next_step.push(
			{
				id,
				dist_matrix[point][id] + predict(curr_time, unvisited, id)
			});
		}
		auto next_point = next_step.top();
		next_step = decltype(next_step)();
		unvisited.erase(next_point.id);

		route.push_back(
		{
			next_point.id,
			{curr_time, next_point.priority}
		});
		curr_time += next_point.priority;
	}

	return route;
}

} // namespace tracer
