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
    mouse_events_{0} {}

void MyApp::setup() {
  ci::audio::SourceFileRef bgm_file = ci::audio::load
          (ci::app::loadAsset(kDefaultBGM));
  background_music_ = ci::audio::Voice::create(bgm_file);
  background_music_->start();
  background_music_->setVolume(0.5);

  ci::Rand::randomize();
  portal_x_ = ci::Rand::randFloat(kBeginningBirdX + kDefaultBirdWidth, 2560);
  portal_y_ = ci::Rand::randFloat(0, 1000);

  bird_ = {kBeginningBirdX, kBeginningBirdY};
}

void MyApp::update() {
  if (!background_music_->isPlaying()) {
      background_music_->start();
  }
  timeline_.step(0.01);
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

void MyApp::mouseDown(cinder::app::MouseEvent event) {
    auto bounce = ch::makeProcedure<ci::vec2>( 2.0,
            [] ( ch::Time t, ch::Time duration ) {
        return ci::vec2( 0, - sin
        (ch::easeInOutQuad((float) t) * 6 * M_PI ) * 100.0f);
    } );

    // Create a ramp phrase that moves from left-to-right.
    auto slide = ch::makeRamp(ci::vec2(0,0),
            ci::vec2(event.getX() - bird_.value()[0],
                    event.getY()- bird_.value()[1]), 2.0f, ch::EaseInOutCubic() );

    // Combine the slide and bounce phrases using an AccumulatePhrase.
    const std::shared_ptr<choreograph::Phrase<glm::vec2>>
            bounceAndSlide = ch::makeAccumulator<ci::vec2>( ci::vec2
                    (bird_.value()[0], bird_.value()[1] ), bounce, slide);

    timeline_.apply(&bird_, bounceAndSlide);

    //if (mouse_events_ < 1) {
        //target_ = {event.getX(), event.getY()};
        //timeline_.apply(&bird_)
                //.then<ch::RampTo>(target_, 0.1);
    //}
    mouse_events_++;

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
      bird_.value()[0], bird_.value()[1], bird_.value()[0] +
      kDefaultBirdWidth, bird_.value()[1] + kDefaultBirdHeight});
}

void MyApp::DrawPortal() {
  portal_texture_ = ci::gl::Texture2d::create(
          loadImage(loadAsset(kDefaultPortal)));

  cinder::gl::draw(portal_texture_, {
      portal_x_, portal_y_, portal_x_ +
      kDefaultPortalWidth, portal_y_ + kDefaultPortalHeight});
}

}  // namespace myapp
