//
// Created by shen0 on 5/3/2020.
//

#ifndef FINALPROJECT_BIRD_H
#define FINALPROJECT_BIRD_H

#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <choreograph/Choreograph.h>

namespace bird {

class Bird {
 public:
  Bird();
  void DrawBird();
  void Reset();
 private:
  void CurveRampTo(float x, float y);
  void SlideRampTo(float x, float y);
  ch::Output<ci::vec2> bird_;
  ci::gl::Texture2dRef bird_texture_;
  ch::Timeline timeline_;
  std::shared_ptr<choreograph::Phrase<glm::vec2>> ramp_;
};

}

#endif //FINALPROJECT_BIRD_H
