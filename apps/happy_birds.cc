// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "happy_birds.h"

#include <cinder/app/App.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include <cinder/audio/Voice.h>
#include "cinder/Rand.h"
#include <choreograph/Choreograph.h>
#include <birdgame/distance_util.h>

using namespace ci::audio;

namespace birdapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;

const std::string kDefaultBird = "bird.png";
const std::string kDefaultBGM = "game-bgm.mp3";
const std::string kDefaultBackground = "game-background.jpg";
const std::string kDefaultPortal = "portal.png";

// These made it look right in Photoshop.
// I might have them vary with getWindowBounds() later
// So the window can be adjustable size.
const float kDefaultBirdWidth = 200;
const float kDefaultBirdHeight = 190;
const float kBeginningBirdX = 400;

const float kDefaultGroundHeight = 1250;
const float kDefaultPortalWidth = 178;
const float kDefaultPortalHeight = 305;

BirdApp::BirdApp()
    : num_points_{0} {}

void BirdApp::setup() {
  ci::audio::SourceFileRef bgm_file = ci::audio::load
          (ci::app::loadAsset(kDefaultBGM));
  background_music_ = ci::audio::Voice::create(bgm_file);
  background_music_->start();
  background_music_->setVolume(0.5);

  ci::Rand::randomize();
  portal_x_ = ci::Rand::randFloat(kBeginningBirdX + kDefaultBirdWidth, 2560);
  portal_y_ = ci::Rand::randFloat(0, 1000);

  bird_ = {kBeginningBirdX, kDefaultGroundHeight - kDefaultBirdHeight};
  is_level_complete_ = false;
  is_auto_aiming_ = false;
  mouse_event_count_ = 0;
}

void BirdApp::update() {
  if (!background_music_->isPlaying()) {
      background_music_->start();
  }

  /*
  if (birdgame::DistanceUtil::GetManhattanDistance(bird_.value()[0],
          bird_.value()[1], portal_x_, portal_y_) < (float) 100 && !is_auto_aiming_) {
      timeline_.clear();
      AimRamp(portal_x_ - (kDefaultBirdWidth / 2),
              portal_y_ - (kDefaultBirdHeight / 2));
      timeline_.apply(&bird_, ramp_);
      is_auto_aiming_ = true;
  } */

  timeline_.step(0.01);
}

void BirdApp::draw() {
  cinder::gl::clear();
  ci::gl::color(Color::white());

  DrawBackground();
  DrawPortal();
  DrawBird();
}

void BirdApp::keyDown(KeyEvent event) {
}

void BirdApp::mouseDown(cinder::app::MouseEvent event) {
    if (mouse_event_count_ < 1) {
        AimRamp(event.getX(), event.getY());
        timeline_.apply(&bird_, ramp_);
    }
    mouse_event_count_++;
}

void BirdApp::DrawBackground() {
  bg_texture_ = ci::gl::Texture2d::create(
        loadImage(loadAsset(kDefaultBackground)));
  cinder::gl::draw(bg_texture_, getWindowBounds());
}

void BirdApp::DrawBird() {
  bird_texture_ = ci::gl::Texture2d::create(
          loadImage(loadAsset(kDefaultBird)));
  cinder::gl::draw(bird_texture_, {
      bird_.value()[0], bird_.value()[1], bird_.value()[0] +
      kDefaultBirdWidth, bird_.value()[1] + kDefaultBirdHeight});
}

void BirdApp::DrawPortal() {
  portal_texture_ = ci::gl::Texture2d::create(
          loadImage(loadAsset(kDefaultPortal)));

  cinder::gl::draw(portal_texture_, {
      portal_x_, portal_y_, portal_x_ +
      kDefaultPortalWidth, portal_y_ + kDefaultPortalHeight});
}

void BirdApp::AimRamp(float x, float y) {
    // Creates a procedure that bounces half a sine wave.
    auto bounce = ch::makeProcedure<ci::vec2>( 0.25,
            [] ( ch::Time t, ch::Time duration ) {
        return ci::vec2( 0, - 10 * sin
        (ch::easeInOutQuad((float) t) * M_PI ) * 50.0f);
    } );

    // Creates a ramp phase that moves from  the bird's
    // current location to the mouse click location.
    auto slide = ch::makeRamp(ci::vec2(0,0),
            ci::vec2(x - bird_.value()[0],y
            - bird_.value()[1]), 0.25f, ch::EaseInOutCubic());

    // Combines the phrases using an AccumulatePhrase.
    ramp_ = ch::makeAccumulator<ci::vec2>(ci::vec2
                    (bird_.value()[0], bird_.value()[1]), bounce, slide);
}
}  // namespace birdapp
