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

		std::vector<Waypoint> points;

		std::vector<int> priorities;

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
		std::vector<time_t> time_priorities;

		/* Index of the nearest closing point.
		 * A common cursor for time_priorities, priorities, point vectors */
		int upcoming;

		/* Point id -> index in time_priorities, priorities, points */
		std::unordered_map<int, int> pointIdToIndex;
};

} // namespace route_context

#endif //ROUTING_ROUTE_CONTEXT_H
