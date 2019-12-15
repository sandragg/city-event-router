#include <time.h>
#include "place.h"
using namespace timetable;

// TODO: Below is a brute force implementation copied from the Event class.
// Need to choose more appropriate way to store recurring schedule
void Place::AddInterval(const Interval& interval)
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


//	struct tm *start_tm, *end_tm;
//	start_tm = gmtime(&interval.start);
//	end_tm = gmtime(&interval.end);
//
//	int w_day = start_tm->tm_wday;
//	int days_diff = abs(end_tm->tm_wday - w_day);
//	if (end_tm->tm_wday < w_day)
//	{
//		days_diff = 7 - days_diff;
//	}
//
//	start_tm->tm_wday = 0;
//	end_tm->tm_wday = days_diff;
//
//	auto start = week_days[w_day];
//
//	if (count(week_days.begin(), week_days.end(), start) > 1)
//	{
//		// copy day schedule for curr day
//	}
//	else
//	{
//		// modify curr day schedule
//	}
}

void Place::RemoveInterval(const Interval& interval)
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

forward_list<Interval> Place::GetInInterval(const Interval& interval, bool strict) const
{
	forward_list<Interval> inclusions;
	auto prev_interval = inclusions.before_begin();

	for (auto &range : schedule)
	{
		if (range.end <= interval.start) continue;

		inclusions.emplace_after(
				prev_interval,
				strict ? max(range.start, interval.start) : range.start,
				strict ? min(range.end, interval.end) : range.end
		);

		++prev_interval;
	}

	return inclusions;
}

forward_list<Interval> Place::GetAll() const
{
	return forward_list<Interval>(schedule);
}
