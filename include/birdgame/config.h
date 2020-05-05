//
// Created by shen0 on 5/4/2020.
//

#ifndef FINALPROJECT_CONFIG_H
#define FINALPROJECT_CONFIG_H

namespace birdgame {

using cinder::Color;

const std::string kDefaultBird  = "bird.png";
const std::string kDefaultBGM = "game-bgm.mp3";
const std::string kDefaultStartBackground = "start-screen.jpg";
const std::string kDefaultBackground = "game-background.jpg";
const std::string kDefaultEndBackground = "end-screen.jpg";
const std::string kDefaultPortal = "portal.png";
const std::string kDefaultFont = "Arial";

const char kDefaultRestart = 'r';
const char kDefaultPause = 'p';
const char kDefaultQuit = 'q';
const char kDefaultNewGame = 'n';

// These made it look right in Photoshop.
const float kDefaultBirdWidth = 200;
const float kDefaultBirdHeight = 190;
const float kBeginningBirdX = 400;

const float kDefaultGroundHeight = 1250;
const float kDefaultPortalWidth = 178;
const float kDefaultPortalHeight = 305;

const ci::vec2 kDefaultInGameScoreLoc = {2300, 100};
const ci::vec2 kDefaultEndGameScoreLoc = {1285, 900};
const ci::ivec2 kDefaultInGameScoreSize = {400, 150};
const ci::ivec2 kDefaultEndGameScoreSize = {600, 220};
const ci::Color kDefaultScoreColor =
        Color(194.0 / 255.0, 139.0 / 255.0, 46.0 / 255.0);
const size_t kDefaultInGameFontSize = 100;
const size_t kDefaultEndGameFontSize = 300;

const float kDefaultVolume = 0.5;
const float kDefaultRampDuration = 0.25;
const float kDefaultPauseDuration = 0.05;

} //namespace birdgame

#endif //FINALPROJECT_CONFIG_H
