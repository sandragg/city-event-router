#ifndef ROUTING_EVENT_H
#define ROUTING_EVENT_H

#include <forward_list>
#include "timetable.h"


namespace timetable
{

class Event : public Timetable<std::forward_list<Interval>>
{
	public:
		void AddInterval(const Interval& interval) override;

		void RemoveInterval(const Interval& interval) override;

		std::forward_list<Interval> GetInInterval(const Interval& interval, bool strict) const override;

		std::forward_list<Interval> GetAll() const override;

		const Interval* GetImmediate(time_t time) const override;

	private:
		std::forward_list<Interval> schedule;
};

} // namespace timetable


#endif //ROUTING_EVENT_H
