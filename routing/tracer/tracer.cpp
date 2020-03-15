#include "tracer.h"
using namespace tracer;


template<typename End_Cond_Tp, typename Heuristic_Tp>
vector<RoutePoint> traceGraph(DistanceMatrix& dist_matrix, End_Cond_Tp&& is_end, Heuristic_Tp&& predict)
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
		// need to update curr_time and include min stay in place time
		// how and where? :)
		for (auto& id : unvisited)
		{
			next_step.push(
				{
					id,
					dist_matrix[point][id] // here? base duration + distance
					+ predict(
						curr_time + dist_matrix[point][id],
						unvisited,
						id)
				});
		}
		auto next_point = next_step.top();
		// maybe here you should set final time duration for previous step.
		curr_time += dist_matrix[point][next_point.id];

		route.push_back(
			{
				next_point.id,
				{curr_time, next_point.priority} // ???
			});
		next_step = decltype(next_step)();
		unvisited.erase(next_point.id);
	}

	return route;
}
