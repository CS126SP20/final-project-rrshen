//
// Created by shen0 on 5/4/2020.
//

#ifndef FINALPROJECT_CONFIG_H
#define FINALPROJECT_CONFIG_H

namespace birdgame {

using cinder::Color;

// --- Filenames of the images of different birds ---
const std::string kDefaultBird  = "bird.png";
const std::string kBouncyBird = "bouncy-bird.png";
const std::string kFastBird = "fast-bird.png";
const std::string kWobblyBird = "wobbly-bird.png";

// --- Filenames of important game elements ---
const std::string kBackgroundMusic = "game-bgm.mp3";
const std::string kStartBackground = "start-screen.jpg";
const std::string kDefaultBackground = "game-background.jpg";
const std::string kEndBackground = "end-screen.jpg";
const std::string kPortal = "portal.png";

// --- Characters that prompt changes in the game ---
const char kRestartKey = 'r';
const char kPauseKey = 'p';
const char kQuitKey = 'q';
const char kNewGameKey = 'n';
const char kSpeciesKey = 's';
const char kFlightKey = ' ';

// --- Heights and widths of different birds ---
const size_t kDefaultBirdWidth = 200;
const size_t kDefaultBirdHeight = 190;
const size_t kBouncyBirdWidth = 210;
const size_t kBouncyBirdHeight = 250;
const size_t kFastBirdWidth = 200;
const size_t kFastBirdHeight = 190;
const size_t kWobblyBirdWidth = 190;
const size_t kWobblyBirdHeight = 185;

// --- Values governing the bird's position and movement ---
// Due to the heavy use of Choreograph and RandFloat in my code, all
// coordinates and functions dealing with them are saved as floats.
const float kBeginningBirdX = 400;
const float kTimelineStepSize = 0.01;
const int kArcAmplitude = -500;
const int kWobbleAmplitude = 50;
const float kRampDuration = 0.25;
const float kWobbleDuration = 0.05;
const float kPauseDuration = 0.05;
const int kBounceHeight = 100;
const int kBounceWidth = 300;

// --- Sizes of important game elements ---
const size_t kGroundHeight = 1250;
const size_t kSkyWidth = 2560;
const size_t kPortalWidth = 178;
const size_t kPortalHeight = 305;
const size_t kPortalGravityRadius = 150;
const float kDefaultVolume = 0.5;

// --- Values that pertain to the printed score ---
const ci::vec2 kInGameScoreLoc = {2300, 100};
const ci::vec2 kEndGameScoreLoc = {1285, 900};
const ci::ivec2 kInGameScoreSize = {400, 150};
const ci::ivec2 kEndGameScoreSize = {600, 220};
const ci::Color kScoreColor =
        Color(194.0 / 255.0, 139.0 / 255.0, 46.0 / 255.0);
const size_t kInGameScoreFontSize = 100;
const size_t kEndGameScoreFontSize = 300;
const std::string kScoreFont = "Arial";

}  // namespace birdgame

#endif //FINALPROJECT_CONFIG_H
