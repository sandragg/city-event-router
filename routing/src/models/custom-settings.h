#ifndef ROUTING_CUSTOM_SETTINGS_H
#define ROUTING_CUSTOM_SETTINGS_H

#include <iostream>
#include <vector>
#include "../timetable/interval.h"
#include "./priority-point.h"


/**
 * Preferences used in routing computing.
 */
struct CustomSettings
{
	/**
	 * Default constructor.
	 * Sets the default settings:
	 *  - #min_stay_time = 1;
	 *  - #late_fee = 1;
	 *  - #time_before_open_fee = 1;
	 *  - #extra_time_fee = 1;
	 *  - #points_priorities = *nullptr*;
	 *  - #time_range = *nullptr*;
	 */
	CustomSettings();
	/**
	 * Minimal time to spend at a point.
	 */
	time_t min_stay_time;
	/**
	 * Penalty coefficient for being late to a point.
	 */
	time_t late_fee;
	/**
	 * Penalty coefficient for being at a point before it's opened.
	 */
	time_t time_before_open_fee;
	/**
	 * Fee coefficient for spending more than #min_stay_time at a point.
	 */
	time_t extra_time_fee;
	/**
	 * A collection of priorities for each point.
	 */
	std::vector<PriorityPoint<int>> *points_priorities;
	/**
	 * Time range limitation for route.
	 */
	timetable::Interval *time_range;
};


#endif //ROUTING_CUSTOM_SETTINGS_H
