#include <catch2/catch.hpp>
#include <vector>
#include "../timetable/event.h"
#include "../distance-matrix/distance-matrix.h"
#include "../models/waypoint.h"
#include "route-context.h"


TEST_CASE("Route context", "[RouteContext]")
{
//	timetable::Event schedule;
//	schedule.AddInterval({ 0, 1 });
//	schedule.AddInterval({ 7, 10 });
//	schedule.AddInterval({ 2, 4 });
//	schedule.AddInterval({ 4, 5 });
	size_t amount = 4;

	std::vector<Waypoint> points(amount);
	std::vector<timetable::Interval> schedule({
		{ 0, 20 },
		{ 5, 15 },
		{ 0, 20 },
		{ 5, 10 }
	});

	for (int i = 0; i < points.size(); i++)
	{
		points[i].id = i;
		points[i].schedule.AddInterval(schedule[i]);
	}

	DistanceMatrix mtx(points.size());
	mtx.Assign(0, 1, 1);
	mtx.Assign(0, 2, 4);
	mtx.Assign(0, 3, 6);
	mtx.Assign(1, 2, 2);
	mtx.Assign(1, 3, 4);
	mtx.Assign(2, 3, 3);

	SECTION("Create context with default settings")
	{
		CustomSettings settings;
		route_context::RouteContext ctx(mtx, points);

		SECTION("Check default settings")
		{
			REQUIRE(ctx.LateFee() == settings.late_fee);
			REQUIRE(ctx.ExtraTimeFee() == settings.extra_time_fee);
			REQUIRE(ctx.MinStayTime() == settings.min_stay_time);
			REQUIRE(ctx.TimeBeforeOpenFee() == settings.time_before_open_fee);
			REQUIRE(ctx.TimeRange() == settings.time_range);
		}
		SECTION("Check point default priority")
		{
			auto default_priority = 1;
			REQUIRE(ctx.PointPriority(points.front().id) == default_priority);
		}
	}

	SECTION("Create context with custom settings")
	{
		CustomSettings settings;
		route_context::RouteContext ctx(mtx, points, settings);

		SECTION("Check custom settings")
		{
			REQUIRE(ctx.LateFee() == settings.late_fee);
			REQUIRE(ctx.ExtraTimeFee() == settings.extra_time_fee);
			REQUIRE(ctx.MinStayTime() == settings.min_stay_time);
			REQUIRE(ctx.TimeBeforeOpenFee() == settings.time_before_open_fee);
			REQUIRE(ctx.TimeRange() == settings.time_range);
		}
	}
}
