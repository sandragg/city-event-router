#include "event.h"


namespace timetable
{

void Event::AddInterval(const Interval& interval)
{
	auto prev_interval = schedule.before_begin();

	for (auto first = schedule.begin(); first != schedule.end(); ++first)
	{
		if (first->start > interval.start)
		{
			break;
		}
		prev_interval = first;
	}

	schedule.insert_after(prev_interval, interval);
}

void Event::RemoveInterval(const Interval& interval)
{
	auto prev_interval = schedule.before_begin();

	for (auto first = schedule.begin(); first != schedule.end(); ++first)
	{
		if (*first == interval)
		{
			schedule.erase_after(prev_interval);
			break;
		}
		prev_interval = first;
	}
}

std::forward_list<Interval> Event::GetInInterval(const Interval& interval, bool strict) const
{
	std::forward_list<Interval> inclusions;
	auto prev_interval = inclusions.before_begin();

	for (auto &range : schedule)
	{
		if (range.end <= interval.start) continue;
		if (range.start >= interval.end) break;

		inclusions.emplace_after(
			prev_interval,
			strict ? std::max(range.start, interval.start) : range.start,
			strict ? std::min(range.end, interval.end) : range.end
		);

		++prev_interval;
	}

	return inclusions;
}

std::forward_list<Interval> Event::GetAll() const
{
	return std::forward_list<Interval>(schedule);
}

const Interval* Event::GetImmediate(time_t time) const
{
	for (auto &range : schedule)
	{
		if (range.end <= time) continue;
		return &range;
	}
	return nullptr;
}

} // namespace timetable
