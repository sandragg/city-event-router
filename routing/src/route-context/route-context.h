#ifndef ROUTING_ROUTE_CONTEXT_H
#define ROUTING_ROUTE_CONTEXT_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include "../distance-matrix/distance-matrix.h"
#include "../timetable/interval.h"
#include "../models/waypoint.h"
#include "../models/custom-settings.h"


/**
 * Includes classes and utils for storing and processing data about a specific route.
 */
namespace route_context
{

/**
 * Stores all custom data and current state based on time.
 * RouteContext stores route preferences and provides methods
 * for working with data and changing time status.
 *
 * @note Custom **preferences** are **immutable**.
 * @note Only *upcoming* cursor changes in time and serves as an indicator of time.
 */
class RouteContext
{
	public:
		/**
		 * Create RouteContext with default settings.
		 * @param dist_matrix
		 * @param waypoints
		 */
		RouteContext(
			const class DistanceMatrix &dist_matrix,
			const std::vector<Waypoint> &waypoints);
		/**
		 * Create RouteContext with provided custom settings.
		 * @param dist_matrix
		 * @param waypoints
		 * @param settings
		 */
		RouteContext(
			const class DistanceMatrix &dist_matrix,
			const std::vector<Waypoint> &waypoints,
			const CustomSettings &settings);
		/**
		 * RouteContext destructor.
		 */
		~RouteContext();
		/**
		 * Update route time status.
		 * Call function on every tick in order to update cursor
		 * to the upcoming point.
		 *
		 * @param now Current time
		 */
		void UpdateOnNewTick(time_t now);
		/**
		 * Go to the next upcoming point.
		 * @note The behavior is undefined if there is no upcoming point.
		 * Call #UpcomingExists first.
		 */
		void SkipUpcomingPoint();
		/**
		 * Check if the point is open *now*.
		 * Method looks for time in the point's schedule.
		 * Thus, any point in time can be passed as an argument.
		 *
		 * @param now Current time
		 * @param point_id %Point id
		 * @return If open - **true**, otherwise - **false**.
		 */
	 	bool IsPointOpen(time_t now, int point_id) const;
	 	/**
	 	 * Get time difference between *now* and the point's opening time.
	 	 * Method looks for time in the point's schedule.
		 * Thus, any point in time can be passed as an argument.
	 	 *
	 	 * @param now Current time
		 * @param point_id %Point id
	 	 * @return If there is no interval now or later - #PastTime,
	 	 * 		if point is open now - 0,
	 	 * 		otherwise - time difference.
	 	 */
		time_t TimeBeforePointOpen(time_t now, int point_id) const;
		/**
		 * Get priority of a point with a *point_id*.
		 * @param point_id %Point id
		 * @return %Point priority
		 * @throw std::out_of_range Point doesn't exist
		 */
		int PointPriority(int point_id) const;
		/**
		 * Get distance matrix.
		 */
		const DistanceMatrix& DistanceMatrix() const;
		/**
		 * Check if there is any upcoming point.
		 */
		bool UpcomingExists() const;
		/**
		 * Get upcoming time.
		 */
		time_t UpcomingTime() const;
		/**
		 * Get upcoming point id.
		 */
		int UpcomingPointId() const;
		/**
		 * Get the passed time indicator.
		 */
		int PastTime() const;
		/**
		 * Get late fee.
		 */
		time_t LateFee() const;
		/**
		 * Get time before open fee.
		 */
		time_t TimeBeforeOpenFee() const;
		/**
		 * Get extra time fee.
		 */
		time_t ExtraTimeFee() const;
		/**
		 * Get minimum stay time.
		 */
		time_t MinStayTime() const;
		/**
		 * Get time interval for route.
		 */
		const timetable::Interval* TimeRange() const;

	private:
		/*
		 * User preferences
		 */

		/** Distance matrix. */
		const class DistanceMatrix *dist_matrix;
		/** Way points. */
		std::vector<Waypoint> points;
		/** Points priorities. */
		std::vector<int> *priorities;
		/** Minimum stay time. */
		time_t min_stay_time;
		/** Late fee coefficient. */
		time_t late_fee;
		/** Time before open fee coefficient. */
		time_t time_before_open_fee;
		/** Extra time fee coefficient. */
		time_t extra_time_fee;
		/**  Available time interval for route. */
		timetable::Interval *time_range;

		/*
		 * Payload for tracer
		 */

		/** Passed time indicator. */
		const static int PAST_TIME = -1;
		/**
		 * Sorted vector of points closing time.
		 */
		std::vector<time_t> time_priorities;
		/**
		 * Index of the nearest closing point.
		 * A common cursor for #time_priorities, #priorities and #points vectors.
		 *
		 * @note Cursor is equal to RouteContext::PAST_TIME if there is no upcoming point.
		 */
		int upcoming;
		/**
		 * Map of point id to index.
		 * A common index in #time_priorities, #priorities, #points vectors.
		 */
		std::unordered_map<int, int> point_id_to_index;

		/**
		 * Route context general initialization.
		 * Method initialize all required properties.
		 *
		 * @note It only depends on #time_range in custom settings.
		 * Ensure time interval definition first.
		 *
		 * @param points
		 */
		void BaseInitialization(const std::vector<Waypoint>& points);
		/**
		 * Compute the latest available time to visit a point.
		 * @param point
		 * @return The latest available time to visit a point.
		 */
		time_t ComputePointClosingTime(const Waypoint &point) const;
};

} // namespace route_context


#endif //ROUTING_ROUTE_CONTEXT_H
