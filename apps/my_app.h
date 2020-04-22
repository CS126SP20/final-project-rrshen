// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <cinder/audio/Voice.h>

using namespace ci::audio;

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseMove(cinder::app::MouseEvent) override;

 private:
  void DrawBackground();
  void DrawBird();
  void DrawPortal();

  ci::gl::Texture2dRef bg_texture_;
  ci::gl::Texture2dRef bird_texture_;
  ci::gl::Texture2dRef portal_texture_;
  VoiceRef background_music_;
  bool isLevelComplete_;

  float bird_x_;
  float bird_y_;
  float portal_x_;
  float portal_y_;

  /*
  struct Point {
    ch::Output<ci::vec2>  _position;
    ci::Color             _color;
  };

  std::vector<ci::vec2> _segments;
  std::array<ci::vec2, 4> curve_points_;

  ch::Output<ci::vec2>  _control_a;
  ch::Output<ci::vec2>  _control_b;
  ch::Output<ci::vec2>  _curve_point; */
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
