// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <cinder/audio/Voice.h>
#include <choreograph/Choreograph.h>

using namespace ci::audio;

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  //void mouseMove(cinder::app::MouseEvent) override;
  void mouseDown(cinder::app::MouseEvent event) override;

 private:
  void DrawBackground();
  void DrawBird();
  void DrawPortal();

  ci::gl::Texture2dRef bg_texture_;
  ci::gl::Texture2dRef bird_texture_;
  ci::gl::Texture2dRef portal_texture_;
  VoiceRef background_music_;
  bool isLevelComplete_;

  ci::vec2 bird_pos_;
  ci::vec2 target_;
  float portal_x_;
  float portal_y_;
  size_t mouse_events_;

  ch::Output<ci::vec2> bird_ = bird_pos_;
  ch::Timeline timeline_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
