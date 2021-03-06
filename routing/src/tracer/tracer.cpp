#include "tracer.h"

#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "../tree/iterators/depth-first-search.h"
#include "../models/priority-point.h"


namespace tracer
{

template <class Tp>
bool RoutePoint<Tp>::operator>(const RoutePoint &rhs) const
{
	return time.start > rhs.time.start;
}

template <class Tp>
bool RoutePoint<Tp>::operator<(const RoutePoint &rhs) const
{
	return time.start < rhs.time.start;
}

template <class Tp>
bool RoutePoint<Tp>::operator==(const RoutePoint &rhs) const
{
	return id == rhs.id;
}

template <class Tp>
bool Route<Tp>::operator>(const Route &rhs) const
{
	if (points.size() != rhs.points.size())
		return points.size() > rhs.points.size();

	if (duration != rhs.duration)
		return duration < rhs.duration;

	if (movement_time != rhs.movement_time)
		return movement_time < rhs.movement_time;

	return points < rhs.points;
}

template <class Tp>
bool Route<Tp>::operator<(const Route &rhs) const
{
	return !(*this == rhs || *this > rhs);
}

template <class Tp>
bool Route<Tp>::operator==(const Route &rhs) const
{
	return duration == rhs.duration
		&& movement_time == rhs.movement_time
		&& points.size() == rhs.points.size()
		&& points == rhs.points;
}

template<class End_Cond_Tp, class Heuristic_Tp, class Time_Calculator_Tp>
list_of_siblings::Tree<RoutePoint<int>>
trace_graph(
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
	size_t id_counter = 0;

	list_of_siblings::Tree<RoutePoint<int>> routes(matrix_size);
	// 1) add entry point as a root in a routes tree
	routes.Append(RoutePoint<int> { id_counter++, 0 });
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
				unvisited.insert(visited_point->meta);
				visited_point = routes.GetParent(visited_point);

			} while (visited_point != next_point_parent);

			auto parent_id = next_point_parent->meta;
			auto current_point_id = current_point.Get()->meta;
			/* Mark next point as visited */
			unvisited.erase(current_point_id);
			/* Reset time to a start time at the next point */
			curr_time = next_point_parent->time.start
				+ dist_matrix[parent_id][current_point_id];
			/* Add time duration at the parent point */
			calc_start_time(parent_id, curr_time);

			continue;
		}
		auto point = (*current_point).meta;
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
			std::vector<RoutePoint<int>> children;
			PriorityPoint<time_t> child;
			while (!next_step.empty())
			{
				child = next_step.top();
				next_step.pop();
				children.emplace_back(RoutePoint<int> { id_counter++, child.id });
			}
			routes.Append(current_point.Get(), children);
		}

		++current_point;
		auto next_point = *current_point;
		// duration for previous step will be computed later or independently.
		// cause routes tree is shared and duration at one point for different routes is different too
		curr_time += dist_matrix[point][next_point.meta];

		unvisited.erase(next_point.meta);
	}

	return routes;
}

template <class Tp>
void extract_routes(
	const list_of_siblings::Tree<Tp> &tree,
	std::priority_queue<Route<Tp>> &routes)
{
	std::stack<typename list_of_siblings::Tree<Tp>::const_iterator> trace_stack;
	Route<Tp> route;

	trace_stack.push(tree.Root());
	while (!trace_stack.empty())
	{
		route.points.push_back(*trace_stack.top());
		auto next_node = tree.GetLeftMostChild(trace_stack.top());
		if (next_node == tree.End())
			routes.push(route);
		while (next_node == tree.End())
		{
			auto current_node = trace_stack.top();
			trace_stack.pop();
			route.points.pop_back();
			if (trace_stack.empty()) return;
			next_node = tree.GetRightSibling(current_node);
		}
		trace_stack.push(next_node);
	}
}

template <class Tp>
std::vector<Route<Tp>>
find_matched_routes(const list_of_siblings::Tree<Tp> &tree, size_t limit)
{
	if (!limit || tree.Empty()) return {};

	std::priority_queue<Route<Tp>> priority_routes;
	extract_routes(tree, priority_routes);

	std::vector<Route<Tp>> result(std::min(priority_routes.size(), limit));
	for (auto &route : result)
	{
		route = priority_routes.top();
		priority_routes.pop();
	}

	return result;
}

} // namespace tracer
