#include <cinder/app/App.h>
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include <choreograph/Choreograph.h>
#include <birdgame/config.h>
#include <birdgame/bird.h>

namespace bird {

using namespace birdgame;

Bird::Bird() : bird_{}, timeline_{}, ramp_{} {}

void Bird::DrawBird() {
  bird_texture_ = ci::gl::Texture2d::create
          (loadImage(ci::app::loadAsset(kDefaultBird)));
  cinder::gl::draw(bird_texture_, {
      bird_.value()[0], bird_.value()[1], bird_.value()[0] +
      kDefaultBirdWidth, bird_.value()[1] + kDefaultBirdHeight});
}

void Bird::UpdateBird() {
  timeline_.step(0.01);
}

void Bird::ResetBird() {
  timeline_.clear();
  bird_ = {kBeginningBirdX, kDefaultGroundHeight - kDefaultBirdHeight};
}

void Bird::CurveRampTo(float x, float y) {
  timeline_.clear();

  // Creates a procedure that bounces half a sine wave.
  auto bounce = ch::makeProcedure<ci::vec2>(kDefaultRampDuration,
          [] ( ch::Time t, ch::Time duration ) {
      return ci::vec2( 0, - 10 * sin
      (ch::easeInOutQuad((float) t) * M_PI ) * 50.0f);
  } );

  // Creates a ramp phase that moves from  the bird's
  // current location to the mouse click location.
  auto slide = ch::makeRamp(ci::vec2(0,0),
          ci::vec2(x - bird_.value()[0],y
          - bird_.value()[1]), kDefaultRampDuration, ch::EaseInOutCubic());

  // Combines the phrases using an AccumulatePhrase.
  ramp_ = ch::makeAccumulator<ci::vec2>(ci::vec2
          (bird_.value()[0], bird_.value()[1]), bounce, slide);

  timeline_.apply(&bird_, ramp_);
}

void Bird::SlideRampTo(float x, float y) {
  timeline_.clear();
  ramp_ = ch::makeRamp(ci::vec2(bird_.value()[0], bird_.value()[1]),
          ci::vec2(x,y), kDefaultRampDuration, ch::EaseInOutCubic());
  timeline_.apply(&bird_, ramp_);
}

void Bird::PauseRamp(float duration) {
  timeline_.clear();
  ramp_ = ch::makeRamp(ci::vec2(bird_.value()[0], bird_.value()[1]),
          ci::vec2(bird_.value()[0], bird_.value()[1]), duration, ch::EaseInOutCubic());
  timeline_.apply(&bird_, ramp_);
}

bool Bird::RampOver() {
  if (timeline_.timeUntilFinish() == 0) {
      return true;
  } else {
      return false;
  }
}

float Bird::getX() {
  return bird_.value()[0];
}

float Bird::getY() {
  return bird_.value()[1];
}

} //namespace bird