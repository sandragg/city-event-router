#include <catch2/catch.hpp>
#include <forward_list>
#include "event.cpp"

TEST_CASE("Event timetable", "[timetable]")
{
	timetable::Event schedule;

	schedule.AddInterval({ 0, 1 });
	schedule.AddInterval({ 7, 10 });
	schedule.AddInterval({ 2, 4 });
	schedule.AddInterval({ 4, 5 });

	SECTION("Initialize timetable")
	{
		std::forward_list<timetable::Interval> intervals({
			{ 0, 1 },
			{ 2, 4 },
			{ 4, 5 },
			{ 7, 10 }
		});

		REQUIRE(schedule.GetAll() == intervals);
	}

	SECTION("Get timetable in interval")
	{
		timetable::Interval range({3, 8});

		std::forward_list<timetable::Interval> strict_intervals({
			{ 3, 4 },
			{ 4, 5 },
			{ 7, 8 }
		});
		REQUIRE(schedule.GetInInterval(range, true) == strict_intervals);

		std::forward_list<timetable::Interval> intervals({
			{ 2, 4 },
			{ 4, 5 },
			{ 7, 10 }
		});
		REQUIRE(schedule.GetInInterval(range, false) == intervals);
	}

	SECTION("Remove intervals from timetable")
	{
		schedule.RemoveInterval({ 0, 1 });
		schedule.RemoveInterval({ 5, 0 });
		schedule.RemoveInterval({ 5, 10 });

		std::forward_list<timetable::Interval> intervals({
			{ 2, 4 },
			{ 4, 5 },
			{ 7, 10 }
		});

		REQUIRE(schedule.GetAll() == intervals);
	}

}
