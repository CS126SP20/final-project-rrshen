//
// Created by shen0 on 5/6/2020.
//

#ifndef FINALPROJECT_BIRD_TYPE_H
#define FINALPROJECT_BIRD_TYPE_H

namespace bird {

// An enumeration of the types of possible birds in this game.
enum class Species {
  kDefault,
  kBouncy,
  kFast,
  kWobbly,
};

// Finds the height corresponding to the passed species
// @param species the species of bird whose height we want to find
// @return the height of a bird of the given species
const size_t GetHeight(Species species);
// Finds the width corresponding to the passed species
// @param species the species of bird whose width we want to find
// @return the width of a bird of the given species
const size_t GetWidth(Species species);
// Finds the filename that accesses an image of the passed species
// @param species the species of bird whose image we want to find
// @return the filename of the image corresponding to the species
const std::string GetImage(Species species);
// Finds the next species of bird in the enum given a species
// @param species the current species of the bird
// @return the following species of bird in the enum Species
const Species GetNext(Species species);

}  // namespace bird

#endif //FINALPROJECT_BIRD_TYPE_H
