//
// Created by shen0 on 5/3/2020.
//

#ifndef FINALPROJECT_BIRD_H
#define FINALPROJECT_BIRD_H

#include <choreograph/Choreograph.h>
#include <birdgame/bird_type.h>

namespace bird {

// This class models a Bird with an adjustable position on the screen.
class Bird {
 public:
  // Constructs a bird with type kDefault.
  Bird();
  // Sets the bird's position to be the starting position.
  void SetupBird();
  // Draws a bird on the screen at a predetermined location.
  void DrawBird();
  // Updates the position of the bird.
  void UpdateBird();
  // Resets the bird's position, movement, and type to the default.
  void ResetBird();
  // Changes the bird's species.
  void ChangeSpecies();

  // Sets the bird on a curved path to the passed x and y coordinates.
  void ArcBirdTo(float x, float y);
  // Sets the bird on a straight path the passed x and y coordinates.
  void SlideBirdTo(float x, float y);
  // Keeps the bird in place for a set duration.
  void StopBird();
  // Checks whether the bird has completed a movement.
  // This returns false if the bird was not moving before.
  // @return true if the bird completed its movement, and false otherwise.
  bool IsBirdDoneMoving();

  float GetX();
  float GetY();
  Species GetSpecies();

 private:
  Species species_;
  ci::gl::Texture2dRef bird_texture_;
  ch::Output<ci::vec2> bird_pos_;
  ch::Timeline timeline_;
  std::shared_ptr<choreograph::Phrase<glm::vec2>> ramp_;
};

}  // namespace bird

#endif //FINALPROJECT_BIRD_H
