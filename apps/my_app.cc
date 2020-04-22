// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include <cinder/audio/Voice.h>

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
const char kDefaultBox[] = "box.png";

MyApp::MyApp() { }

void MyApp::setup() {
  ci::audio::SourceFileRef bgm_file = ci::audio::load
          (ci::app::loadAsset(kDefaultBGM));
  background_music_ = ci::audio::Voice::create(bgm_file);
  background_music_->start();
}

void MyApp::update() {
  if (!background_music_->isPlaying()) {
      background_music_->start();
  }
}

void MyApp::draw() {
  cinder::gl::clear();
  ci::gl::color(Color::white());
  DrawBackground();
  DrawBird();
  DrawBox();
  DrawPortal();
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::DrawBackground() {
  bg_texture_ = ci::gl::Texture2d::create(
        loadImage(loadAsset(kDefaultBackground)));
  cinder::gl::draw(bg_texture_, getWindowBounds());
}

void MyApp::DrawBird() {
  bird_texture_ = ci::gl::Texture2d::create(
          loadImage(loadAsset(kDefaultBird)));
  cinder::gl::draw(bird_texture_);
}

void MyApp::DrawBox() {
  box_texture_ = ci::gl::Texture2d::create(
          loadImage(loadAsset(kDefaultBox)));
  cinder::gl::draw(box_texture_);
}

void MyApp::DrawPortal() {
  portal_texture_ = ci::gl::Texture2d::create(
          loadImage(loadAsset(kDefaultPortal)));
  cinder::gl::draw(portal_texture_);
}

}  // namespace myapp
