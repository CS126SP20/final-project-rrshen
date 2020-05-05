// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <birdgame/config.h>

namespace birdgame {

using std::string;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;

// Code copied from Snake
void PrintText(const std::string& text, const ci::Color& color, const cinder::ivec2& size,
        const cinder::vec2& location, const size_t& font_size) {
    cinder::gl::color(color);

    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font(kNormalFont, font_size))
            .size(size)
            .color(color)
            .text(text);

    const auto box_size = box.getSize();
    const cinder::vec2 loc = {location.x - box_size.x / 2, location.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, loc);
}

}  // namespace birdgame
