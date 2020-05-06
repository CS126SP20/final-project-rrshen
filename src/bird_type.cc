// Copyright (c) 2020 Rachel Shen. All rights reserved.

#include <cinder/app/App.h>
#include "cinder/gl/gl.h"
#include <choreograph/Choreograph.h>
#include <birdgame/config.h>
#include <birdgame/bird.h>

namespace bird {

using namespace birdgame;

const size_t GetHeight(Species species) {
  switch (species) {
    case Species::kBouncy:
        return kBouncyBirdHeight;
    case Species::kFast:
        return kFastBirdHeight;
    case Species::kWobbly:
        return kWobblyBirdHeight;
    default:
        return kDefaultBirdHeight;
  }
}
const size_t GetWidth(Species species) {
  switch (species) {
    case Species::kBouncy:
        return kBouncyBirdWidth;
    case Species::kFast:
        return kFastBirdWidth;
    case Species::kWobbly:
        return kWobblyBirdWidth;
    default:
        return kDefaultBirdWidth;
  }
}
const std::string GetImage(Species species) {
  switch (species) {
    case Species::kBouncy:
        return kBouncyBird;
    case Species::kFast:
        return kFastBird;
    case Species::kWobbly:
        return kWobblyBird;
    default:
        return kDefaultBird;
  }
}

const Species GetNext(Species species) {
  switch (species) {
      case Species::kDefault:
          return Species::kBouncy;
      case Species::kBouncy:
          return Species::kFast;
      case Species::kFast:
          return Species::kWobbly;
      default:
          return Species::kDefault;
  }
}

}  // namespace bird