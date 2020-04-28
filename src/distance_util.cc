// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <birdgame/distance_util.h>

#include <cmath>

namespace birdapp {

static float GetManhattanDistance(float x1, float y1, float x2, float y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

}  // namespace birdapp
