#include <iostream>
#include "timetable/event.h"


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

	return 0;
}