#include <catch2/catch.hpp>
#include "tracer.h"
#include "../models/waypoint.h"
#include "../route-context/route-context.h"

#include "../tracer-strategies/base.h"


void init_waypoints(std::vector<Waypoint> &waypoints);
void init_distance_matrix(DistanceMatrix &mtx);
void initialize_tree(list_of_siblings::Tree<std::string> &tree);
bool check_routes_equality(
	const std::vector<tracer::Route<std::string>>& routes,
	const std::vector<std::vector<std::string>>& expected_routes);

TEST_CASE("Get all routes", "[tracer]")
{
	list_of_siblings::Tree<std::string> routes_tree(32);
	initialize_tree(routes_tree);

	auto routes = tracer::find_matched_routes(routes_tree, 100);
	std::vector<std::vector<std::string>> expected_result =
	{
		{ "O", "C1", "C2.1.1", "C3.1.1.1", "C4.1.1.1.1" },
		{ "O", "A1", "A2.1.2", "A3.1.2.1" },
		{ "O", "A1", "A2.1.2", "A3.1.2.2" },
		{ "O", "B1", "B2.1.1", "B3.1.1.1" },
		{ "O", "C1", "C2.1.1", "C3.1.1.2" },
		{ "O", "A1", "A2.1.1" },
		{ "O", "A1", "A2.1.3" },
		{ "O", "C1", "C2.1.2" }
	};

	SECTION("Ordered by priority")
	{
		REQUIRE(check_routes_equality(routes, expected_result));
	}

	SECTION("Ordered alphabetically")
	{
		std::sort(
			routes.begin(),
			routes.end(),
			[](const tracer::Route<std::string>& lhs, const tracer::Route<std::string>& rhs)
			{
				return lhs.points < rhs.points;
			});

		std::sort(expected_result.begin(), expected_result.end());

		REQUIRE(check_routes_equality(routes, expected_result));
	}
}

TEST_CASE("Get up to N routes ordered by priority", "[tracer]")
{
	std::vector<Waypoint> waypoints;
	init_waypoints(waypoints);

	DistanceMatrix dist(4);
	init_distance_matrix(dist);

	route_context::RouteContext ctx(dist, waypoints);
	auto routes_tree = tracer::trace_graph(
		dist,
		is_end(ctx),
		predict,
		calculate_start_time);
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
}

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

void initialize_tree(list_of_siblings::Tree<std::string> &tree)
{
	tree.Append("O");
	tree.Append(tree.Root(), {"A1", "B1", "C1"}); // A1, B1, C1
	tree.Append(tree.Find("A1"), {"A2.1.1", "A2.1.2", "A2.1.3"}); // A2.1.1, A2.1.2, A2.1.3
	tree.Append(tree.Find("B1"), {"B2.1.1"}); // B2.1.1
	tree.Append(tree.Find("C1"), {"C2.1.1", "C2.1.2"}); // C2.1.1, C2.1.2
	tree.Append(tree.Find("A2.1.2"), {"A3.1.2.1", "A3.1.2.2"}); // A3.1.2.1, A3.1.2.2
	tree.Append(tree.Find("B2.1.1"), {"B3.1.1.1"}); // B3.1.1.1
	tree.Append(tree.Find("C2.1.1"), {"C3.1.1.1", "C3.1.1.2"}); // C3.1.1.1, C3.1.1.2
	tree.Append(tree.Find("C3.1.1.1"), {"C4.1.1.1.1"}); // C4.1.1.1.1
}

bool check_routes_equality(
	const std::vector<tracer::Route<std::string>>& routes,
	const std::vector<std::vector<std::string>>& expected_routes)
{
	if (routes.size() != expected_routes.size()) return false;
	for (size_t i = 0; i < routes.size(); i++)
	{
		if (routes[i].points != expected_routes[i]) return false;
	}
	return true;
}

