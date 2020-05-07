// Copyright (c) 2020 Rachel Shen. All rights reserved.

#include <cmath>

namespace birdgame {

// Code inspired by Mineopoly
float GetEuclideanDistance(float x1, float y1, float x2, float y2) {

  // The 2 squares (x1 - x2) and (y1 - y2), as per the distance formula.
  return (float) sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

}  // namespace birdgame
