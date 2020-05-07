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

const std::shared_ptr<choreograph::Phrase<glm::vec2>>
GetFlight(Species species) {
  // Code derived from:
  // https://github.com/sansumbrella/Choreograph/blob/master/samples/src/samples/SlideAndBounce.cpp

  // Creates a procedure that arcs half a sine wave.
  auto arc = ch::makeProcedure<ci::vec2>(kRampDuration,
          [] ( ch::Time t, ch::Time duration ) {
      return ci::vec2( 0, kArcAmplitude * sin
      (ch::easeInOutQuad((float) t) * M_PI ));
  } );

  // Creates a procedure that arcs multiple sine waves.
  auto wobble = ch::makeProcedure<ci::vec2>(kWobbleDuration,
          [] ( ch::Time t, ch::Time duration ) {
      return ci::vec2( 0, kWobbleAmplitude * sin
      (ch::easeInOutQuad((float) t) * M_PI ));
  } );

  switch (species) {
    case Species::kWobbly:
      return wobble;
    default:
      return arc;
  }
}

}  // namespace bird