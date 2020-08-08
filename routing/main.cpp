#include <iostream>
#include "src/timetable/event.h"
#include "src/distance-matrix/distance-matrix.h"
#include "src/tracer/tracer.h"
#include "src/route-context/route-context.h"
#include "src/tracer-strategies/default.h"


void init_waypoints(std::vector<Waypoint> &waypoints)
{
	std::vector<timetable::Interval> schedule;
	schedule.emplace_back(0, 20);
	schedule.emplace_back(5, 15);
	schedule.emplace_back(0, 20);
	schedule.emplace_back(5, 10);

	waypoints.resize(4);
	for (int i = 0; i < waypoints.size(); i++)
	{
		waypoints[i].id = i;
		waypoints[i].schedule.AddInterval(schedule[i]);
	}
}

void init_distance_matrix(DistanceMatrix &mtx)
{
	mtx.Assign(0, 1, 1);
	mtx.Assign(0, 2, 4);
	mtx.Assign(0, 3, 6);
	mtx.Assign(1, 2, 2);
	mtx.Assign(1, 3, 4);
	mtx.Assign(2, 3, 3);
}

int main()
{
	std::vector<Waypoint> waypoints;
	init_waypoints(waypoints);

	DistanceMatrix dist(4);
	init_distance_matrix(dist);

	route_context::RouteContext ctx(dist, waypoints);
	auto routes_tree = tracer::trace_graph(
		dist,
		is_end(ctx),
		predict(ctx),
		calculate_start_time(ctx));
	auto routes = tracer::find_matched_routes(routes_tree, 100);

	for (auto &route : routes)
	{
		std::cout
			<< "duration = " << route.duration << ", "
			<< "driving time = " << route.movement_time << ":"
			<< std::endl;
		for (auto &point : route.points)
		{
			std::cout
				<< point.id
				<< " (" << point.time.start << "; " << point.time.end << ")"
				<< std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}
