#ifndef ROUTING_CUSTOM_SETTINGS_H
#define ROUTING_CUSTOM_SETTINGS_H

#include <iostream>
#include <vector>
#include "../timetable/interval.h"
#include "./priority-point.h"


struct CustomSettings
{
	CustomSettings();

	time_t min_stay_time;
	time_t late_fee;
	time_t time_before_open_fee;
	time_t extra_time_fee;

	/* pair<point id, priority>  */
	std::vector<PriorityPoint<int>> *points_priorities;

	timetable::Interval *time_range;
};


#endif //ROUTING_CUSTOM_SETTINGS_H
