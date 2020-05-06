//
// Created by shen0 on 5/4/2020.
//

#ifndef FINALPROJECT_TEXT_PRINT_UTIL_H
#define FINALPROJECT_TEXT_PRINT_UTIL_H

namespace birdgame {

// This function prints the passed string in the passed color
// At the passed location with the passed size and font size.

// @param text the text to be printed
// @param color the color to print the text with
// @param size the width and height of the text-box
// @param loc the coordinates of the center of the text-box
// @param font_size the font size of the text
void PrintText(const std::string& text, const ci::Color& color,
        const ci::ivec2& size, const ci::vec2& loc, const size_t& font_size);

}  // namespace birdgame

#endif //FINALPROJECT_TEXT_PRINT_UTIL_H
