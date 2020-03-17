#ifndef ROUTING_TIMETABLE_H
#define ROUTING_TIMETABLE_H

#include <ctime>
#include "interval.h"


namespace timetable
{

template<class _Tp>
class Timetable
{
	public:
		virtual void AddInterval(const Interval &interval) = 0;

		virtual void RemoveInterval(const Interval &interval) = 0;

		virtual _Tp GetInInterval(const Interval &interval, bool strict) const = 0;

		virtual _Tp GetAll() const = 0;
};

} // namespace timetable


#endif //ROUTING_TIMETABLE_H
