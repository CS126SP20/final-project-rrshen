#include <birdgame/bird.h>
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <choreograph/Choreograph.h>

namespace bird {

const std::string kDefaultBird = "bird.png";
const float kDefaultBirdWidth = 200;
const float kDefaultBirdHeight = 190;
const float kBeginningBirdX = 400;
}
/*
 * public:
  Bird();
  DrawBird();
  Reset();
 private:
  void CurveRampTo(float x, float y);
  void SlideRampTo(float x, float y);
  ch::Output<ci::vec2> bird_;
  ci::gl::Texture2dRef bird_texture_;
  ch::Timeline timeline_;
  std::shared_ptr<choreograph::Phrase<glm::vec2>> ramp_;
}
 */