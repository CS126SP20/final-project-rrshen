// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <birdgame/distance_util.h>


TEST_CASE("Test Get Euclidean Distance", "[distance_util]") {
  SECTION("Horizontal Distances") {
      REQUIRE(birdgame::GetEuclideanDistance(0.0f, 0.0f, 1.0f, 0.0f) == 1.0f);
  }
  SECTION ("Vertical Distances") {
      REQUIRE(birdgame::GetEuclideanDistance(1.0f, 0.0f, 1.0f, 2.0f) == 2.0f);
  }
  SECTION ("Diagonal Distances") {
      REQUIRE(birdgame::GetEuclideanDistance(0.0f, 2.0f, 3.0f, 6.0f) == 5.0f);
  }
  SECTION ("Distances with Negatives") {
      REQUIRE(birdgame::GetEuclideanDistance(-4.0f, -6.0f, 5.0f, 6.0f) == 15.0f);
  }
}