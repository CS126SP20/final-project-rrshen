// Copyright (c) 2020 Rachel Shen. All rights reserved.

#include "happy_birds.h"

#include <cinder/app/App.h>
#include "cinder/ImageIo.h"
#include <cinder/Font.h>
#include <cinder/Text.h>
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include <cinder/audio/Voice.h>
#include "cinder/Rand.h"
#include <choreograph/Choreograph.h>
#include <birdgame/distance_util.h>
#include <birdgame/config.h>
#include <birdgame/bird.h>


using namespace ci::audio;
using namespace birdgame;

namespace birdapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;

BirdApp::BirdApp()
    : num_points_{0},
      state_ {GameState::kStartScreen},
      is_paused_ {false},
      is_game_over_ {false} {}

void BirdApp::setup() {
  ci::audio::SourceFileRef bgm_file = ci::audio::load
          (ci::app::loadAsset(kDefaultBGM));
  background_music_ = ci::audio::Voice::create(bgm_file);
  background_music_->start();
  background_music_->setVolume(kDefaultVolume);
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
  if (GetEuclideanDistance(bird_x, bird_y,
          ending_x_, ending_y_) < (float) 200 &&
          state_ == GameState::kLaunched) { //get rid of magic number >:(
      timeline_.clear();
      SlideRampTo(ending_x_, ending_y_);
      timeline_.apply(&bird_, ramp_);
      state_ = GameState::kAutoAiming;
  }

  timeline_.step(0.01);

  if (timeline_.timeUntilFinish() == 0) {
      if (is_game_over_) {
          state_ = GameState::kEndScreen;
      } else if (state_ == GameState::kAutoAiming) {
          num_points_++;
          ResetLevel();
      } else if (state_ == GameState::kLaunched) {
          PauseRamp(kDefaultPauseDuration);
          timeline_.apply(&bird_, ramp_);
          is_game_over_ = true;
      }
  }
}

void BirdApp::draw() {
  cinder::gl::clear();
  ci::gl::color(Color::white());

  DrawBackground();
  if (state_ != GameState::kStartScreen &&
  state_ != GameState::kEndScreen) {
      DrawPortal();
      DrawBird();
  }
}

void BirdApp::keyDown(KeyEvent event) {
    if (state_ == GameState::kStartScreen ||
    (state_ == GameState::kPlaying &&
    event.getChar() == kDefaultRestart)) {
        ResetLevel();
    } else if (event.getChar() == kDefaultQuit) {
        state_ = GameState::kEndScreen;
    } else if (event.getChar() == kDefaultPause) {
        is_paused_ = !is_paused_;
    } else if (state_ == GameState::kEndScreen &&
    event.getChar() == kDefaultNewGame) {
        num_points_ = 0;
        is_paused_ = false;
        state_ = GameState::kStartScreen;
        is_game_over_ = false;
        ResetLevel();
    }
}

void BirdApp::mouseDown(cinder::app::MouseEvent event) {
    if (!is_paused_ && !has_clicked_in_level_) {
        state_ = GameState::kLaunched;
        float random_add_to_x = ci::Rand::randFloat(-200,200);
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
  } else if (state_ == GameState::kEndScreen) {
      bg_texture_ = ci::gl::Texture2d::create(
              loadImage(loadAsset(kDefaultEndBackground)));
      // TODO: Print score
  } else {
      bg_texture_ = ci::gl::Texture2d::create(
              loadImage(loadAsset(kDefaultBackground)));
      //PrintText("Game Over :(", color, size, center);
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
}

void BirdApp::SlideRampTo(float x, float y) {
  ramp_ = ch::makeRamp(ci::vec2(bird_.value()[0], bird_.value()[1]),
          ci::vec2(x,y), kDefaultRampDuration, ch::EaseInOutCubic());
}

void BirdApp::PauseRamp(float duration) {
  ramp_ = ch::makeRamp(ci::vec2(bird_.value()[0], bird_.value()[1]),
          ci::vec2(bird_.value()[0], bird_.value()[1]), duration, ch::EaseInOutCubic());
}

void BirdApp::ResetLevel() {
  ci::Rand::randomize();
  portal_x_ = ci::Rand::randFloat(kBeginningBirdX + kDefaultBirdWidth, 2560);
  portal_y_ = ci::Rand::randFloat(0, kDefaultGroundHeight - kDefaultPortalHeight);
  ending_x_ = portal_x_ - (kDefaultBirdWidth / 2);
  ending_y_ = portal_y_ + (kDefaultPortalHeight / 2) - (kDefaultBirdHeight / 2);

  bird_ = {kBeginningBirdX, kDefaultGroundHeight - kDefaultBirdHeight};
  state_ = GameState::kPlaying;
  has_clicked_in_level_ = false;
}

}  // namespace birdapp
