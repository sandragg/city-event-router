#include "tracer.h"
using namespace tracer;


template<typename End_Cond_Tp, typename Heuristic_Tp>
list_of_siblings::Tree<RoutePoint> traceGraph(DistanceMatrix& dist_matrix, End_Cond_Tp&& is_end, Heuristic_Tp&& predict)
{
	auto matrix_size = dist_matrix.Size();

	unordered_set<int> unvisited;
	for (int i = 1; i < matrix_size; i++)
		unvisited.insert(i);

	time_t curr_time = 0;

	list_of_siblings::Tree<RoutePoint> routes;
	// 1) add entry point as a root in a routes tree
	routes.Append(RoutePoint{ 1 });
	tree::DfsIterator<decltype(routes)> current_point(routes);

	while (!current_point.IsEnd())
	{
		if (is_end(curr_time, unvisited)) // change time when go back !!!
		{
			auto visited_point = current_point.Get();

			++current_point;
			if (current_point.IsEnd()) break;

			/* Revert visited points to unvisited */
			auto next_point_parent = routes.GetParent(current_point.Get());
			do
			{
				unvisited.insert(visited_point->id);
				visited_point = routes.GetParent(visited_point);

			} while (visited_point != next_point_parent);
			/* Mark next point as visited */
			unvisited.erase(current_point.Get()->id);

			continue;
		}
		auto point = (*current_point).id;

		{
			// need to update curr_time and include min stay in place time
			// how and where? :)
			priority_queue<
				PriorityPoint<time_t>,
				vector<PriorityPoint<time_t>>,
				greater<>
			> next_step;

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
			// 2) pop all elements from queue and add as children of the current node in a routes tree
			vector<RoutePoint> children;
			PriorityPoint<time_t> child;
			while (!next_step.empty())
			{
				child = next_step.top();
				next_step.pop();
				children.emplace_back(RoutePoint{ child.id });
			}
			routes.Append(current_point.Get(), children);
		}

		++current_point;
		auto next_point = *current_point;
		// maybe here you should set final time duration for previous step.
		curr_time += dist_matrix[point][next_point.id];

		unvisited.erase(next_point.id);
	}

	return routes;
}
