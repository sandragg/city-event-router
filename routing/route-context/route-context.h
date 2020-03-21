#ifndef ROUTING_ROUTE_CONTEXT_H
#define ROUTING_ROUTE_CONTEXT_H

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <vector>
#include "../distance-matrix/distance-matrix.h"
#include "../timetable/interval.h"
#include "../models/waypoint.h"
#include "../models/priority-point.h"


namespace route_context
{

class RouteContext
{
	public:
		RouteContext() {}

		void UpdateOnNewTick(time_t now);
	 	bool IsPointOpen(time_t now, int point_id) const;
		time_t TimeBeforePointOpen(time_t now, int point_id) const;

		int PointPriority(int point_id) const;
		const DistanceMatrix& DistanceMatrix() const;
		bool UpcomingExists() const;
		time_t UpcomingTime() const;
		int UpcomingPointId() const;
		bool PastTime() const;
		time_t LateFee() const;
		time_t TimeBeforeOpenFee() const;
		time_t ExtraTimeFee() const;
		time_t MinStayTime() const;

	private:
		/*
		 * User preferences
		 */
		class DistanceMatrix *dist_matrix;

		/* Point id -> point */
		std::unordered_map<int, Waypoint> points;

		/* Point id -> priority */
		std::unordered_map<int, int> priorities;

		time_t min_stay_time;

		/* Coefficients ans fees */
		time_t late_fee;
		time_t time_before_open_fee;
		time_t extra_time_fee;

		/* Available time interval for route.
		 * Maybe time_range will be squashed in time_priorities */
		timetable::Interval time_range;

		/*
		 * Payload for tracer
		 */
		const static int PAST_TIME = -1;

		/* Sorted vector of points closing time */
		std::vector<PriorityPoint<time_t>> time_priorities;

		/* Iterator to the nearest closing point in time_priorities */
		std::vector<PriorityPoint<time_t>>::iterator upcoming;
};

} // namespace route_context

#endif //ROUTING_ROUTE_CONTEXT_H
