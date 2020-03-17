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


namespace route_context
{

class RouteContext
{
	public:
		RouteContext() {}
		void UpdateOnNewTick(time_t now);
	 	bool IsPointOpen(int point_id) const;
		time_t TimeBeforePointOpen(int point_id) const;

		int PointPriority(int point_id) const;
		const DistanceMatrix& DistanceMatrix() const;
		time_t UpcomingTime() const;
		int UpcomingPointId() const;

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
		/* Sorted vector of points closing time */
		std::vector<time_t> time_priorities;

		/* Point id -> index in time_priorities */
		std::unordered_map<int, int> pointIdToIndex;

		/* Iterator to the nearest closing point in time_priorities */
		std::vector<time_t>::iterator upcoming;
};

} // namespace route_context

#endif //ROUTING_ROUTE_CONTEXT_H
