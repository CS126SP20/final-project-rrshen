// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include <cinder/audio/Voice.h>
#include "cinder/Rand.h"
#include <Box2D/Common/b2BlockAllocator.h>
#include <limits>

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
    bird_x_{kBeginningBirdX},
    bird_y_{kBeginningBirdY} {}

void MyApp::setup() {
  ci::audio::SourceFileRef bgm_file = ci::audio::load
          (ci::app::loadAsset(kDefaultBGM));
  background_music_ = ci::audio::Voice::create(bgm_file);
  background_music_->start();

  ci::Rand::randomize();
  portal_x_ = ci::Rand::randFloat(kBeginningBirdX, 2560);
  portal_y_ = ci::Rand::randFloat(0, 1000);

  /*
  float w = (float) getWindowWidth();
  float h = (float) getWindowHeight();
  curve_points_ = {
    ci::vec2( w * 0.08f, h * 0.86f ),
    ci::vec2( w * 0.08f, h * 0.14f ),
    ci::vec2( w * 0.92f, h * 0.14f ),
    ci::vec2( w * 0.92f, h * 0.86f )
  };

  const float duration = 1.5f;

  // Ramp from anchor point to control point.
  auto ramp_a = makeRamp(curve_points_[0], curve_points_[1], duration );
  // Ramp from control point to anchor point.
  auto ramp_b = makeRamp( curve_points_[2], curve_points_[3], duration );

  // Lerp between control ramps.
  auto bezier_point = makeBlend<ci::vec2>( ramp_a, ramp_b, 0.0f );

  timeline().setDefaultRemoveOnFinish( false );

  auto group = std::make_shared<ch::Timeline>();
  group->setDefaultRemoveOnFinish( false );
  group->setRemoveOnFinish( false );

  // Animate our control points along their respective ramps.
  group->apply<ci::vec2>( &_control_a, ramp_a );
  group->apply<ci::vec2>( &_control_b, ramp_b );

  // Animate the mix of the bezier point from a to b.
  group->apply<float>( bezier_point->getMixOutput(), makeRamp( 0.0f, 1.0f, duration ) );

  // Apply the bezier_point animation to our curve point variable.
  group->apply<ci::vec2>( &_curve_point, bezier_point )
    .startFn( [this] {
        _segments.clear();
        _segments.push_back( _curve_points[0] );
    } )
    .updateFn( [this] {
        _segments.push_back( _curve_point );
    } );

  // When all our animations finish, cue the group to restart after a delay.
  group->setFinishFn( [this, group] () {
    timeline()
            .cue( [group] {
                group->resetTime();
            }, 0.5f )
            .removeOnFinish( true );
  } );

  // Move our grouping timeline onto our main timeline.
  // This will update our group as the main timeline progresses.
  timeline().addShared( group );

  // place things at initial timelined values.
  timeline().jumpTo( 0 ); */
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
  DrawPortal();
  DrawBird();
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::mouseMove(cinder::app::MouseEvent event) {
    size_t x = event.getX();
    size_t y = event.getY();
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
      kBeginningBirdX, kBeginningBirdY, kBeginningBirdX +
      kDefaultBirdWidth, kBeginningBirdY + kDefaultBirdHeight});
}

void MyApp::DrawPortal() {
  portal_texture_ = ci::gl::Texture2d::create(
          loadImage(loadAsset(kDefaultPortal)));

  /*
   * cinder::gl::draw(portal_texture_, {
      2000, 800, 2000 + // Hardcoded ahora for testing
      kDefaultPortalWidth, 800 + kDefaultPortalHeight});
   */
  cinder::gl::draw(portal_texture_, {
      portal_x_, portal_y_, portal_x_ +
      kDefaultPortalWidth, portal_y_ + kDefaultPortalHeight});
}

}  // namespace myapp
