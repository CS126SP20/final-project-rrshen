// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include "cinder/gl/Texture.h"
#include <cinder/audio/Voice.h>
#include <birdgame/bird.h>

namespace birdapp {

enum class GameState {
  kStartScreen,
  kPlaying,
  kLaunched,
  kAutoAiming,
  kEndScreen,
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
  void DrawPortal();
  void ResetLevel();

  ci::gl::Texture2dRef bg_texture_;
  ci::gl::Texture2dRef portal_texture_;
  ci::audio::VoiceRef background_music_;

  float portal_x_;
  float portal_y_;
  // ending_x_ and ending_y_ represent the final x and y positions
  // of a bird that passes the level. These are a fixed distance away
  // from the portal, set using the portal and bird's dimensions
  float ending_x_;
  float ending_y_;

  size_t num_points_;
  bool is_game_over_;
  GameState state_;
  bool has_clicked_in_level_;
  bool is_paused_;
  bird::Bird bird_;
};

}  // namespace birdapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
