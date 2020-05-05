//
// Created by shen0 on 5/4/2020.
//

#ifndef FINALPROJECT_CONFIG_H
#define FINALPROJECT_CONFIG_H

namespace birdgame {

const std::string kDefaultBird  = "bird.png";
const std::string kDefaultBGM = "game-bgm.mp3";
const std::string kDefaultStartBackground = "start-screen.jpg";
const std::string kDefaultBackground = "game-background.jpg";
const std::string kDefaultEndBackground = "end-screen.jpg";
const std::string kDefaultPortal = "portal.png";

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

const float kDefaultInGameScoreX = 2200;
const float kDefaultInGameScoreY = 20;
const float kDefaultEndGameScoreX = 1300;
const float kDefaultEndGameScoreY = 850;
/*
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 50};
    const Color color = Color::black(); */

const float kDefaultVolume = 0.5;
const float kDefaultRampDuration = 0.25;
const float kDefaultPauseDuration = 0.05;

} //namespace birdgame

#endif //FINALPROJECT_CONFIG_H
