// Copyright (c) 2020 Rachel Shen. All rights reserved.

#include "happy_birds.h"

#include <cinder/app/App.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include <cinder/audio/Voice.h>
#include "cinder/Rand.h"
#include <choreograph/Choreograph.h>
#include <birdgame/distance_util.h>
//#include <birdgame/bird.h>

using namespace ci::audio;

namespace birdapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;

const std::string kDefaultBird = "bird.png";
const std::string kDefaultBGM = "game-bgm.mp3";
const std::string kDefaultStartBackground = "start-screen.jpg";
const std::string kDefaultBackground = "game-background.jpg";
const std::string kDefaultEndBackground = "end-screen.jpg";
const std::string kDefaultPortal = "portal.png";
const char kDefaultRestart = 'r';
const char kDefaultPause = 'p';

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
    : num_points_{0},
      state_ {GameState::kStartScreen},
      is_paused_ {false} {}

void BirdApp::setup() {
  ci::audio::SourceFileRef bgm_file = ci::audio::load
          (ci::app::loadAsset(kDefaultBGM));
  background_music_ = ci::audio::Voice::create(bgm_file);
  background_music_->start();
  background_music_->setVolume(0.5);
}

void BirdApp::update() {
  if (is_paused_) {
      background_music_->pause();
      return;
  }
  if (!background_music_->isPlaying()) {
      background_music_->start();
  }

  float bird_x = bird_.value()[0];
  float bird_y = bird_.value()[1];
  if (birdgame::DistanceUtil::GetManhattanDistance(bird_x,
          bird_y, ending_x_, ending_y_) < (float) 300 && state_ == GameState::kPlaying) { //get rid of magic number >:(
      timeline_.clear();
      SlideRampTo(ending_x_, ending_y_);
      timeline_.apply(&bird_, ramp_);
      state_ = GameState::kAutoAiming;
  }

  timeline_.step(0.01);

  if (bird_x == ending_x_ && bird_y == ending_y_ && state_ == GameState::kAutoAiming) {
      // Fade to black?
      time_at_portal_ = std::chrono::system_clock::now();
      state_ = GameState::kLevelOver;
  }

  double elapsed_time =
          std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
          - time_at_portal_).count();

  if (elapsed_time > 3 && state_ == GameState::kLevelOver) {
      ResetLevel();
      num_points_++;
  }
}

void BirdApp::draw() {
  cinder::gl::clear();
  ci::gl::color(Color::white());

  DrawBackground();
  if (state_ != GameState::kStartScreen) {
      DrawPortal();
      DrawBird();
  }
}

void BirdApp::keyDown(KeyEvent event) {
    if (state_ == GameState::kStartScreen) {
        ResetLevel();
    } else if (event.getChar() == kDefaultRestart) {
        ResetLevel();
    } else if (event.getChar() == kDefaultPause) {
        is_paused_ = !is_paused_;
    }
}

void BirdApp::mouseDown(cinder::app::MouseEvent event) {
    if (!is_paused_ && !has_clicked_in_level_) {
        float random_add_to_x = ci::Rand::randFloat(-150,150);
        ci::Rand::randomize();
        CurveRampTo((float) event.getX() + random_add_to_x,
                (float) event.getY() + ci::Rand::randFloat(0, 300));
        timeline_.apply(&bird_, ramp_);
        has_clicked_in_level_ = true;
    }
}

void BirdApp::DrawBackground() {
  if (state_ == GameState::kStartScreen) {
      bg_texture_ = ci::gl::Texture2d::create(
              loadImage(loadAsset(kDefaultStartBackground)));
  } else if (state_ == GameState::kGameOver) {
      bg_texture_ = ci::gl::Texture2d::create(
              loadImage(loadAsset(kDefaultEndBackground)));
      // TODO: Print score
  } else {
      bg_texture_ = ci::gl::Texture2d::create(
              loadImage(loadAsset(kDefaultBackground)));
  }
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

void BirdApp::CurveRampTo(float x, float y) {
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

void BirdApp::SlideRampTo(float x, float y) {
  ramp_ = ch::makeRamp(ci::vec2(bird_.value()[0], bird_.value()[1]),
          ci::vec2(x,y), 0.25f, ch::EaseInOutCubic());
}

void BirdApp::ResetLevel() {
  ci::Rand::randomize();
  portal_x_ = ci::Rand::randFloat(kBeginningBirdX + kDefaultBirdWidth, 2560);
  portal_y_ = ci::Rand::randFloat(0, kDefaultGroundHeight - kDefaultPortalHeight);
  ending_x_ = portal_x_ - 100;
  ending_y_ = portal_y_ + 50;

  bird_ = {kBeginningBirdX, kDefaultGroundHeight - kDefaultBirdHeight};
  state_ = GameState::kPlaying;
  has_clicked_in_level_ = false;
}

}  // namespace birdapp
