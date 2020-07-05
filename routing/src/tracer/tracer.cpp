#include "tracer.h"

#include <vector>
#include <queue>
#include <algorithm>
#include "../tree/iterators/depth-first-search.h"
#include "../models/priority-point.h"


namespace tracer
{

bool RoutePoint::operator==(const RoutePoint &rhs) const
{
	return id == rhs.id && time == rhs.time;
}

template<typename End_Cond_Tp, typename Heuristic_Tp, typename Time_Calculator_Tp>
list_of_siblings::Tree<RoutePoint>
traceGraph(
	DistanceMatrix& dist_matrix,
	End_Cond_Tp&& is_end,
	Heuristic_Tp&& predict,
	Time_Calculator_Tp&& calc_start_time)
{
	auto matrix_size = dist_matrix.Size();

	std::unordered_set<int> unvisited;
	for (int i = 1; i < matrix_size; i++)
		unvisited.insert(i);

	time_t curr_time = 0;

	list_of_siblings::Tree<RoutePoint> routes(matrix_size);
	// 1) add entry point as a root in a routes tree
	routes.Append(RoutePoint {1});
	tree::DfsIterator<decltype(routes)> current_point(routes);

	while (!current_point.IsEnd())
	{
		if (is_end(curr_time, unvisited))
		{
			auto visited_point = current_point.Get();
			visited_point->time.start = curr_time;

			++current_point;
			if (current_point.IsEnd()) break;

			/* Revert visited points to unvisited */
			auto next_point_parent = routes.GetParent(current_point.Get());
			do
			{
				unvisited.insert(visited_point->id);
				visited_point = routes.GetParent(visited_point);

			} while (visited_point != next_point_parent);

			auto parent_id = next_point_parent->id;
			auto current_point_id = current_point.Get()->id;
			/* Mark next point as visited */
			unvisited.erase(current_point_id);
			/* Reset time to a start time at the next point */
			curr_time = next_point_parent->time.start
				+ dist_matrix[parent_id][current_point_id];
			/* Add time duration at the parent point */
			calc_start_time(parent_id, curr_time);

			continue;
		}
		auto point = (*current_point).id;
		// set start time (considering time before open) + increase curr_time on min stay time
		(*current_point).time.start = calc_start_time(point, curr_time);
		{
			std::priority_queue<
				PriorityPoint<time_t>,
				std::vector<PriorityPoint<time_t>>,
				std::greater<>
			> next_step;

			for (auto& id : unvisited)
			{
				next_step.push(
					{
						id,
						dist_matrix[point][id] // probably this distance is redundant
						+ predict(
							curr_time + dist_matrix[point][id],
							unvisited,
							id)
					});
			}
			// 2) pop all elements from queue and add as children of the current node in a routes tree
			std::vector<RoutePoint> children;
			PriorityPoint<time_t> child;
			while (!next_step.empty())
			{
				child = next_step.top();
				next_step.pop();
				children.emplace_back(RoutePoint {child.id});
			}
			routes.Append(current_point.Get(), children);
		}

		++current_point;
		auto next_point = *current_point;
		// duration for previous step will be computed later or independently.
		// cause routes tree is shared and duration at one point for different routes is different too
		curr_time += dist_matrix[point][next_point.id];

		unvisited.erase(next_point.id);
	}

	return routes;
}

} // namespace tracer
