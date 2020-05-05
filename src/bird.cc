// Copyright (c) 2020 Rachel Shen. All rights reserved.

#include <cinder/app/App.h>
#include "cinder/gl/gl.h"
#include <choreograph/Choreograph.h>
#include <birdgame/config.h>
#include <birdgame/bird.h>

namespace bird {

using namespace birdgame;

Bird::Bird() : bird_pos_{}, timeline_{}, ramp_{} {}

void Bird::DrawBird() {
  bird_texture_ = ci::gl::Texture2d::create
          (loadImage(ci::app::loadAsset(kDefaultBird)));
  cinder::gl::draw(bird_texture_, {
      GetX(), GetY(), GetX() +
      kBirdWidth, GetY() + kBirdHeight});
}

void Bird::UpdateBird() {
  timeline_.step(kTimelineStepSize);
}

void Bird::ResetBird() {
  timeline_.clear();
  bird_pos_ = {kBeginningBirdX, kGroundHeight - kBirdHeight};
}

void Bird::CurveRampTo(float x, float y) {
  timeline_.clear();

  // Creates a procedure that bounces half a sine wave.
  auto bounce = ch::makeProcedure<ci::vec2>(kRampDuration,
          [] ( ch::Time t, ch::Time duration ) {
      return ci::vec2( 0, kCurveRampAmplitude * sin
      (ch::easeInOutQuad((float) t) * M_PI ));
  } );

  // Creates a ramp phase that moves from  the bird's
  // current location to the mouse click location.
  auto slide = ch::makeRamp(ci::vec2(0,0),
          ci::vec2(x - GetX(),y
          - GetY()), kRampDuration, ch::EaseInOutCubic());

  // Combines the phrases using an AccumulatePhrase.
  ramp_ = ch::makeAccumulator<ci::vec2>(ci::vec2
          (GetX(), GetY()), bounce, slide);

  timeline_.apply(&bird_pos_, ramp_);
}

void Bird::SlideRampTo(float x, float y) {
  timeline_.clear();
  ramp_ = ch::makeRamp(ci::vec2(GetX(), GetY()),
          ci::vec2(x,y), kRampDuration, ch::EaseInOutCubic());
  timeline_.apply(&bird_pos_, ramp_);
}

void Bird::PauseRamp(float duration) {
  timeline_.clear();
  ramp_ = ch::makeRamp(ci::vec2(GetX(), GetY()),
          ci::vec2(GetX(), GetY()), duration, ch::EaseInOutCubic());
  timeline_.apply(&bird_pos_, ramp_);
}

bool Bird::IsRampOver() {
  return (timeline_.timeUntilFinish() == 0);
}

float Bird::GetX() {
  return bird_pos_.value()[0];
}

float Bird::GetY() {
  return bird_pos_.value()[1];
}

} //namespace bird