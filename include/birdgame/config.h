//
// Created by shen0 on 5/4/2020.
//

#ifndef FINALPROJECT_CONFIG_H
#define FINALPROJECT_CONFIG_H

namespace birdgame {

using cinder::Color;

const std::string kDefaultBird  = "bird.png";
const std::string kBackgroundMusic = "game-bgm.mp3";
const std::string kStartBackground = "start-screen.jpg";
const std::string kDefaultBackground = "game-background.jpg";
const std::string kEndBackground = "end-screen.jpg";
const std::string kPortal = "portal.png";
const std::string kFont = "Arial";

const char kRestartKey = 'r';
const char kPauseKey = 'p';
const char kQuitKey = 'q';
const char kNewGameKey = 'n';

// These made it look right in Photoshop.
const float kBirdWidth = 200;
const float kBirdHeight = 190;
const float kBeginningBirdX = 400;
const float kTimelineStepSize = 0.01;
const float kCurveRampAmplitude = -500;

const float kRandomXRange = 200;
const float kRandomYRange = 300;

const float kGroundHeight = 1250;
const float kSkyWidth = 2560;
const float kPortalWidth = 178;
const float kPortalHeight = 305;
const float kPortalGravityRadius = 150;

const ci::vec2 kInGameScoreLoc = {2300, 100};
const ci::vec2 kEndGameScoreLoc = {1285, 900};
const ci::ivec2 kInGameScoreSize = {400, 150};
const ci::ivec2 kEndGameScoreSize = {600, 220};
const ci::Color kScoreColor =
        Color(194.0 / 255.0, 139.0 / 255.0, 46.0 / 255.0);
const size_t kInGameFontSize = 100;
const size_t kEndGameFontSize = 300;

const float kDefaultVolume = 0.5;
const float kRampDuration = 0.25;
const float kPauseDuration = 0.05;

} //namespace birdgame

#endif //FINALPROJECT_CONFIG_H
