// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;

const char kDefaultBackground[] = "game-background.jpg";

MyApp::MyApp() { }

void MyApp::setup() { }

void MyApp::update() { }

void MyApp::draw() {
  cinder::gl::clear();
  DrawBackground();
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::DrawBackground() {
  cinder::gl::clear(Color(0,0,0));
  ci::gl::color(Color::white());
  bg_texture_ = ci::gl::Texture2d::create(
        loadImage(loadAsset(kDefaultBackground)));
  cinder::gl::draw(bg_texture_);
}

}  // namespace myapp
