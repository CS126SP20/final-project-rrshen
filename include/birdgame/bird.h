//
// Created by shen0 on 5/3/2020.
//

#ifndef FINALPROJECT_BIRD_H
#define FINALPROJECT_BIRD_H

#include <choreograph/Choreograph.h>

namespace bird {

enum class BirdType {
  kDefault,
  kBouncy,
  kFast,
  kWobbly,
};

class Bird {
 public:
  Bird();
  void DrawBird();
  void UpdateBird();
  void ResetBird();

  void CurveRampTo(float x, float y);
  void SlideRampTo(float x, float y);
  void PauseRamp(float duration);
  bool IsRampOver();

  float GetX();
  float GetY();

 private:
  //float GetHeight();
  //const float GetWidth();
  //const std::string GetImage();

  BirdType type_;
  ci::gl::Texture2dRef bird_texture_;
  ch::Output<ci::vec2> bird_pos_;
  ch::Timeline timeline_;
  std::shared_ptr<choreograph::Phrase<glm::vec2>> ramp_;
};

}  // namespace bird

#endif //FINALPROJECT_BIRD_H
