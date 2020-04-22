// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include <cinder/audio/Voice.h>
#include "cinder/Rand.h"
#include <choreograph/Choreograph.h>

using namespace ci::audio;

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;

const char kDefaultBird[] = "bird.png";
const char kDefaultBGM[] = "game-bgm.mp3";
const char kDefaultBackground[] = "game-background.jpg";
const char kDefaultPortal[] = "portal.png";

// These made it look right in Photoshop.
// I might have them vary with getWindowBounds() later
// So the window can be adjustable size.
const float kDefaultBirdWidth = 270;
const float kDefaultBirdHeight = 240;
const float kBeginningBirdX = 250;
const float kBeginningBirdY = 1020;

const float kDefaultPortalWidth = 178;
const float kDefaultPortalHeight = 305;

MyApp::MyApp()
    : isLevelComplete_{false},
    bird_pos_{kBeginningBirdX, kBeginningBirdY},
    mouse_events_{0} {}

void MyApp::setup() {
  ci::audio::SourceFileRef bgm_file = ci::audio::load
          (ci::app::loadAsset(kDefaultBGM));
  background_music_ = ci::audio::Voice::create(bgm_file);
  background_music_->start();

  ci::Rand::randomize();
  portal_x_ = ci::Rand::randFloat(kBeginningBirdX + kDefaultBirdWidth, 2560);
  portal_y_ = ci::Rand::randFloat(0, 1000);

  //bird_ = bird_pos_;
  /*target_ = {1000,100};
  timeline_.apply(&bird_)
  .then<ch::Hold>(bird_pos_, 1.0)
  .then<ch::RampTo>( target_, 3.0 );*/
}

void MyApp::update() {
  if (!background_music_->isPlaying()) {
      background_music_->start();
  }
  //timeline_.step( 1.0 / 60.0 );
}

void MyApp::draw() {
  cinder::gl::clear();
  ci::gl::color(Color::white());

  DrawBackground();
  DrawPortal();
  DrawBird();
}

void MyApp::keyDown(KeyEvent event) {
}

void MyApp::mouseMove(cinder::app::MouseEvent event) {
    if (mouse_events_ < 1) {
        target_ = {event.getX(), event.getY()};
        auto sequence = ch::Sequence<ci::vec2>(bird_.value())
                .then<ch::Hold>(bird_pos_, 1.0)
                .then<ch::RampTo>(target_, 3.0);
        auto current_time = std::chrono::system_clock::now();
        auto duration_in_seconds = std::chrono::duration<double>(current_time.time_since_epoch());
        double num_seconds = duration_in_seconds.count();
        bird_pos_ = sequence.getValue(num_seconds);
    }
    mouse_events_++;
    /*
    timeline_.apply(&bird_)
        .then<ch::Hold>(bird_pos_, 1.0)
            .then<ch::RampTo>( target_, 3.0 ); */
}

void MyApp::DrawBackground() {
  bg_texture_ = ci::gl::Texture2d::create(
        loadImage(loadAsset(kDefaultBackground)));
  cinder::gl::draw(bg_texture_, getWindowBounds());
}

void MyApp::DrawBird() {
  bird_texture_ = ci::gl::Texture2d::create(
          loadImage(loadAsset(kDefaultBird)));
  cinder::gl::draw(bird_texture_, {
      bird_pos_[0], bird_pos_[1], bird_pos_[0] +
      kDefaultBirdWidth, bird_pos_[1] + kDefaultBirdHeight});
}

void MyApp::DrawPortal() {
  portal_texture_ = ci::gl::Texture2d::create(
          loadImage(loadAsset(kDefaultPortal)));

  cinder::gl::draw(portal_texture_, {
      portal_x_, portal_y_, portal_x_ +
      kDefaultPortalWidth, portal_y_ + kDefaultPortalHeight});
}

}  // namespace myapp
