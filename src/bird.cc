// Copyright (c) 2020 Rachel Shen. All rights reserved.

#include <cinder/app/App.h>
#include "cinder/gl/gl.h"
#include <choreograph/Choreograph.h>
#include <birdgame/config.h>
#include <birdgame/bird.h>
#include <birdgame/bird_type.h>

namespace bird {

using namespace birdgame;

Bird::Bird() : species_{Species::kDefault} {}

void Bird::SetupBird() {
  timeline_.clear();
  bird_pos_ = {kBeginningBirdX, kGroundHeight - GetHeight(species_)};
}

void Bird::DrawBird() {
  bird_texture_ = ci::gl::Texture2d::create
          (loadImage(ci::app::loadAsset(GetImage(species_))));

  cinder::gl::draw(bird_texture_, {
      GetX(), GetY(), GetX() +
      GetWidth(species_), GetY() + GetHeight(species_)});
}

void Bird::UpdateBird() {
  timeline_.step(kTimelineStepSize);
}

void Bird::ResetBird() {
  species_ = Species::kDefault;
  timeline_.clear();
  bird_pos_ = {kBeginningBirdX, kGroundHeight - GetHeight(species_)};
}

void Bird::ChangeSpecies() {
  Species former_species = species_;
  species_ = GetNext(former_species);
  bird_pos_ = {GetX() + GetWidth(former_species) - GetWidth(species_),
               GetY() + GetHeight(former_species) - GetHeight(species_)};
}

void Bird::ArcBirdTo(float x, float y) {
  timeline_.clear();

  // Creates a procedure that bounces half a sine wave.
  auto bounce = ch::makeProcedure<ci::vec2>(kRampDuration,
          [] ( ch::Time t, ch::Time duration ) {
      return ci::vec2( 0, kCurveRampAmplitude * sin
      (ch::easeInOutQuad((float) t) * M_PI ));
  } );

  // Creates a ramp phase that moves from  the bird's
  // current location to the passed x and y coordinates.
  auto slide = ch::makeRamp(ci::vec2(0,0),
          ci::vec2(x - GetX(),y
          - GetY()), kRampDuration, ch::EaseInOutCubic());

  // Combines the phrases using an AccumulatePhrase.
  ramp_ = ch::makeAccumulator<ci::vec2>(ci::vec2
          (GetX(), GetY()), bounce, slide);

  timeline_.apply(&bird_pos_, ramp_);
}

void Bird::SlideBirdTo(float x, float y) {
  timeline_.clear();

  ramp_ = ch::makeRamp(ci::vec2(GetX(), GetY()),
          ci::vec2(x,y), kRampDuration, ch::EaseInOutCubic());
  timeline_.apply(&bird_pos_, ramp_);
}

void Bird::StopBird() {
  timeline_.clear();

  // Creates a ramp from its current position to its current position.
  ramp_ = ch::makeRamp(ci::vec2(GetX(), GetY()),
          ci::vec2(GetX(), GetY()), kPauseDuration, ch::EaseInOutCubic());
  timeline_.apply(&bird_pos_, ramp_);
}

bool Bird::IsBirdDoneMoving() {
  return (timeline_.timeUntilFinish() == 0);
}

float Bird::GetX() {
  return bird_pos_.value()[0];
}

float Bird::GetY() {
  return bird_pos_.value()[1];
}

Species Bird::GetSpecies() {
  return species_;
}

}  // namespace bird