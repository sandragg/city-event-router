#include <catch2/catch.hpp>
#include "distance-matrix.h"

TEST_CASE("Distance matrix", "[DistanceMatrix]")
{
	size_t count = 4;
	DistanceMatrix mtx(count);

	REQUIRE(mtx.Size() == count);

	SECTION("Initialize matrix")
	{
		mtx.Assign(0, 1, 1);
		mtx.Assign(0, 2, 4);
		mtx.Assign(0, 3, 6);
		mtx.Assign(1, 2, 2);
		mtx.Assign(1, 3, 4);
		mtx.Assign(2, 3, 3);

		REQUIRE(mtx[0][1] == 1);
		REQUIRE(mtx[0][2] == 4);
		REQUIRE(mtx[0][3] == 6);
		REQUIRE(mtx[1][2] == 2);
		REQUIRE(mtx[1][3] == 4);
		REQUIRE(mtx[2][3] == 3);
	}
}
