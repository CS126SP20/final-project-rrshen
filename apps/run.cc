// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "happy_birds.h"


using cinder::app::App;
using cinder::app::RendererGl;


namespace birdapp {

const int kSamples = 8;
const int kWidth = 2560;
const int kHeight = 1440;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setResizable(false);
  settings->setTitle("Happy Birds");
}

}  // namespace birdapp


// This is a macro that runs the application.
CINDER_APP(birdapp::BirdApp,
           RendererGl(RendererGl::Options().msaa(birdapp::kSamples)),
           birdapp::SetUp)
