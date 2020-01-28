#include <iostream>
#include "timetable/event.h"
#include "distance-matrix/distance-matrix.h"

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

	DistanceMatrix dist(3);

	dist.Assign(1, 0, 1);
	dist.Assign(2, 0, 2);
	dist.Assign(2, 1, 3);

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
			std::cout << dist[i][j] << " ";
		std::cout << std::endl;
	}

	return 0;
}
