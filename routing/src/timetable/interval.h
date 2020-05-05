#ifndef ROUTING_INTERVAL_H
#define ROUTING_INTERVAL_H

#include <ctime>


namespace timetable
{

struct Interval
{
	Interval() : start(0), end(0) {}

	Interval(time_t s, time_t e) : start(s), end(e) {}

	bool operator==(const Interval& rhs) const
	{
		return this->start == rhs.start && this->end == rhs.end;
	}

	time_t start;
	time_t end;
};

} // namespace timetable


#endif //ROUTING_INTERVAL_H
