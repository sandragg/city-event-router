#include "event.h"
using namespace timetable;


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

forward_list<Interval> Event::GetInInterval(const Interval& interval) const
{
	forward_list<Interval> inclusions;
	auto prev_interval = inclusions.before_begin();

	for (auto &range : schedule)
	{
		if (range.end <= interval.start) continue;
		if (range.start >= interval.end) break;

		inclusions.insert_after(
			prev_interval,
			{
				max(range.start, interval.start),
				min(range.end, interval.end)
			});

		++prev_interval;
	}

	return inclusions;
}
