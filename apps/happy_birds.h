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

namespace birdapp {

enum class GameState {
  kStartScreen,
  kPlaying,
  kAutoAiming,
  kLevelOver,
  kGameOver,
};

class BirdApp : public cinder::app::App {
 public:
  BirdApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent event) override;

 private:
  void DrawBackground();
  void DrawBird();
  void DrawPortal();
  void CurveRampTo(float x, float y);
  void SlideRampTo(float x, float y);
  void ResetLevel();

  ci::gl::Texture2dRef bg_texture_;
  ci::gl::Texture2dRef bird_texture_;
  ci::gl::Texture2dRef portal_texture_;
  VoiceRef background_music_;
  float portal_x_;
  float portal_y_;
  float ending_x_; //add comments explaining what this is
  float ending_y_;

  size_t num_points_;
  GameState state_;
  bool has_clicked_in_level_;
  bool is_paused_;
  std::chrono::time_point<std::chrono::system_clock> time_at_portal_;

  ch::Output<ci::vec2> bird_;
  ch::Timeline timeline_;
  std::shared_ptr<choreograph::Phrase<glm::vec2>> ramp_;
  //maybe put ^^this stuff into a bird class
};

}  // namespace birdapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
