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
  void UpdateBird();
  void ResetBird();
  void CurveRampTo(float x, float y);
  void SlideRampTo(float x, float y);
  void PauseRamp(float duration);
  bool RampOver();
  float getX();
  float getY();
 private:
  ci::gl::Texture2dRef bird_texture_;
  ch::Output<ci::vec2> bird_;
  ch::Timeline timeline_;
  std::shared_ptr<choreograph::Phrase<glm::vec2>> ramp_;
};

}

#endif //FINALPROJECT_BIRD_H
