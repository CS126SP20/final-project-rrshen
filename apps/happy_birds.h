// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include "cinder/gl/Texture.h"
#include <cinder/audio/Voice.h>
#include <birdgame/bird.h>

namespace birdapp {

// An enumeration of the game's possible states.
enum class GameState {
  kStartScreen,
  kPlaying,
  kLaunched,
  kAutoAiming,
  kEndScreen,
};

// This class interprets input from the keyboard and mouse and
// modifies the game's display elements accordingly.
class BirdApp : public cinder::app::App {
 public:
  BirdApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent event) override;

 private:
  // Draws the game background, which is dependent on the game's state.
  void DrawBackground();
  // Draws a portal at the location set by ResetLevel().
  void DrawPortal();
  // Restarts a level without affecting the player's previous achievements.
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
  GameState state_;
  bool is_game_over_;
  bool is_paused_;
  bird::Bird bird_;
};

}  // namespace birdapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
