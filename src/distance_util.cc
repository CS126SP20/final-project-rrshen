// Copyright (c) 2020 Rachel Shen. All rights reserved.

#include <cmath>

namespace birdgame {

// Code inspired by Mineopoly
float GetEuclideanDistance(float x1, float y1, float x2, float y2) {
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

}  // namespace birdgame
