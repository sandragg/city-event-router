#ifndef ROUTING_TIMETABLE_H
#define ROUTING_TIMETABLE_H

#include <ctime>
#include "interval.h"

/**
 * Includes utils for working with a schedule.
 */
namespace timetable
{

/**
 * Stores point's schedule.
 * @tparam _Tp Container
 */
template<class _Tp>
class Timetable
{
	public:
		/**
		 * Add working time to schedule.
		 * @param interval
		 */
		virtual void AddInterval(const Interval &interval) = 0;
		/**
		 * Remove working time from schedule.
		 * @param interval
		 */
		virtual void RemoveInterval(const Interval &interval) = 0;
		/**
		 * Get schedule for received *interval*.
		 * @param interval
		 * @param strict 	Strict bounds.
		 * 					If **true** - reduce extreme intervals to lower bounds,
		 * 					**false** - return extreme intervals entirely.
		 * @return Intersection of *interval* and timetable.
		 */
		virtual _Tp GetInInterval(const Interval &interval, bool strict) const = 0;
		/**
		 * Get full schedule.
		 */
		virtual _Tp GetAll() const = 0;
		/**
		 * Get nearest working interval.
		 * Find interval which includes received *time*.
		 * It may be current or one of the following intervals, if one exists,
		 * and null otherwise.
		 *
		 * @param time Current time
		 * @return If *exists* - a pointer to a time interval, otherwise - nullptr.
		 */
		virtual const Interval* GetImmediate(time_t time) const = 0;
};

} // namespace timetable


#endif //ROUTING_TIMETABLE_H
