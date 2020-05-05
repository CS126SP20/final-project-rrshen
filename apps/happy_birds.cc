// Copyright (c) 2020 Rachel Shen. All rights reserved.

#include "happy_birds.h"

#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include <birdgame/distance_util.h>
#include <birdgame/text_print_util.h>
#include <birdgame/config.h>
#include <birdgame/bird.h>

using namespace birdgame;

namespace birdapp {

BirdApp::BirdApp()
    : num_points_{0},
      state_ {GameState::kStartScreen},
      is_paused_ {false},
      is_game_over_ {false},
      bird_ {bird::Bird()} {}

void BirdApp::setup() {
  ci::audio::SourceFileRef bgm_file =
          ci::audio::load(ci::app::loadAsset(kDefaultBGM));
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

  float bird_x = bird_.GetX();
  float bird_y = bird_.GetY();
  if (GetEuclideanDistance(bird_x, bird_y,
          ending_x_, ending_y_) < (float) 200 &&
          state_ == GameState::kLaunched) { //get rid of magic number >:(
      bird_.SlideRampTo(ending_x_, ending_y_);
      state_ = GameState::kAutoAiming;
  }

  bird_.UpdateBird();

  if (bird_.IsRampOver()) {
      if (is_game_over_) {
          state_ = GameState::kEndScreen;
      } else if (state_ == GameState::kAutoAiming) {
          num_points_++;
          ResetLevel();
      } else if (state_ == GameState::kLaunched) {
          bird_.PauseRamp(kDefaultPauseDuration);
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
      bird_.DrawBird();
      std::string score = "Points: " + std::to_string(num_points_);
      PrintText(score, kDefaultScoreColor, kDefaultInGameScoreSize, kDefaultInGameScoreLoc, kDefaultInGameFontSize);
  } else if (state_ == GameState::kEndScreen) {
      std::string score = std::to_string(num_points_);
      PrintText(score, kDefaultScoreColor, kDefaultEndGameScoreSize, kDefaultEndGameScoreLoc, kDefaultEndGameFontSize);
  }
}

void BirdApp::keyDown(ci::app::KeyEvent event) {
    if (state_ == GameState::kStartScreen ||
    (state_ == GameState::kPlaying &&
    event.getChar() == kDefaultRestart)) {
        ResetLevel();
    } else if (event.getChar() == kDefaultQuit) {
        bird_.ResetBird();
        state_ = GameState::kEndScreen;
    } else if (event.getChar() == kDefaultPause) {
        is_paused_ = !is_paused_;
    } else if (state_ == GameState::kEndScreen &&
    event.getChar() == kDefaultNewGame) {
        num_points_ = 0;
        state_ = GameState::kStartScreen;
        is_game_over_ = false;
        ResetLevel();
    }
}

void BirdApp::mouseDown(cinder::app::MouseEvent event) {
    if (!is_paused_ && !has_clicked_in_level_
    && state_ == GameState::kPlaying) {
        state_ = GameState::kLaunched;
        float random_add_to_x = ci::Rand::randFloat(-200,200);
        ci::Rand::randomize();
        bird_.CurveRampTo((float) event.getX() + random_add_to_x,
                (float) event.getY() + ci::Rand::randFloat(0, 300));
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
  } else {
      bg_texture_ = ci::gl::Texture2d::create(
              loadImage(loadAsset(kDefaultBackground)));
  }
  cinder::gl::draw(bg_texture_, getWindowBounds());
}

void BirdApp::DrawPortal() {
  portal_texture_ = ci::gl::Texture2d::create(
          loadImage(loadAsset(kDefaultPortal)));

  cinder::gl::draw(portal_texture_, {
      portal_x_, portal_y_, portal_x_ +
      kDefaultPortalWidth, portal_y_ + kDefaultPortalHeight});
}

void BirdApp::ResetLevel() {
  ci::Rand::randomize();
  portal_x_ = ci::Rand::randFloat(kBeginningBirdX + kDefaultBirdWidth, 2560);
  portal_y_ = ci::Rand::randFloat(0, kDefaultGroundHeight - kDefaultPortalHeight);
  ending_x_ = portal_x_ - (kDefaultBirdWidth / 2);
  ending_y_ = portal_y_ + (kDefaultPortalHeight / 2) - (kDefaultBirdHeight / 2);

  bird_.ResetBird();
  state_ = GameState::kPlaying;
  has_clicked_in_level_ = false;
}

}  // namespace birdapp
