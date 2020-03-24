#include <iostream>
#include <algorithm>
#include "src/timetable/event.h"
#include "src/distance-matrix/distance-matrix.h"
#include "src/tracer/tracer.h"
#include "src/route-context/route-context.h"
#include "src/draft-1.cpp"

extern "C" {
	int foo(int a, int b)
	{
		return a + b;
	}
}


int main()
{
	timetable::Event event_schedule;

	event_schedule.AddInterval({ 0, 1 });
	event_schedule.AddInterval({ 7, 10 });
	event_schedule.AddInterval({ 2, 4 });
	event_schedule.AddInterval({ 4, 5 });

	std::cout << "Add" << std::endl;
	for (auto &interval : event_schedule.GetAll())
	{
		std::cout << "[" << interval.start << ", " << interval.end << "]" << std::endl;
	}

	timetable::Interval range({3, 8});
	std::cout << "Get in interval [" << range.start << ", " << range.end << "]" << std::endl;
	for (auto &interval : event_schedule.GetInInterval(range, true))
	{
		std::cout << "[" << interval.start << ", " << interval.end << "]" << std::endl;
	}

	event_schedule.RemoveInterval({ 0, 1 });
	event_schedule.RemoveInterval({ 5, 0 });
	event_schedule.RemoveInterval({ 5, 10 });

	std::cout << "Remove" << std::endl;
	for (auto &interval : event_schedule.GetAll())
	{
		std::cout << "[" << interval.start << ", " << interval.end << "]" << std::endl;
	}

	DistanceMatrix dist(4);

	dist.Assign(1, 0, 1);
	dist.Assign(1, 2, 2);
	dist.Assign(1, 3, 4);
	dist.Assign(2, 3, 3);
	dist.Assign(2, 0, 4);
	dist.Assign(0, 3, 6);

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
			std::cout << dist[i][j] << " ";
		std::cout << std::endl;
	}

	route_context::RouteContext ctx;
	auto route = tracer::traceGraph(dist, is_end(ctx), predict(ctx));
	for (auto &r : route)
	{
		std::cout
			<< r.id
			<< " (" << r.time.start << "; " << r.time.end << ")"
			<< std::endl;
	}

	return 0;
}
