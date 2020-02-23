#include <iostream>
#include "timetable/event.h"
#include "distance-matrix/distance-matrix.h"
#include "tracer.cpp"
#include <ctime>
#include <unordered_set>

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

	tracer::end_condition is_end = [](time_t now, std::unordered_set<int> unvisited)
	{
		return unvisited.empty();
	};
	tracer::heuristic predict = [](time_t now, std::unordered_set<int> unvisited, int next_vertex)
	{
		return (time_t)0;
	};
	auto route = tracer::traceGraph(dist, is_end, predict);
	for (auto &r : route)
	{
		std::cout
			<< r.id
			<< " (" << r.time.start<< "; "<< r.time.end << ")"
			<< std::endl;
	}

	return 0;
}
