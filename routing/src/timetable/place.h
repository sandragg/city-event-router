#ifndef ROUTING_PLACE_H
#define ROUTING_PLACE_H

#include <forward_list>
#include <array>
#include "timetable.h"


namespace timetable
{

enum WeekDay {
	Sunday = 0,
	Monday = 1,
	Tuesday = 2,
	Wednesday = 3,
	Thursday = 4,
	Friday = 5,
	Saturday = 6,
	EveryDay = 7
};

class Place : public Timetable<std::forward_list<Interval>>
{
	public:
		void AddInterval(const Interval& interval) override;

		void RemoveInterval(const Interval& interval) override;

		std::forward_list<Interval> GetInInterval(const Interval& interval, bool strict) const override;

		std::forward_list<Interval> GetAll() const override;

	private:
		// TODO: Choose appropriate data structure for repetitive schedule
		std::forward_list<Interval> schedule;
};

} // namespace timetable


/*
 * MTWTh
 * 123
 *
 * (MT + 34)
 * MT   WTh
 * 1234 123
 *
 * (W - 3)
 * MT   W  Th
 * 1234 12 123
 *
 * (T - 234)
 * M    T W  Th
 * 1234 1 12 123
 *
 */


#endif //ROUTING_PLACE_H
