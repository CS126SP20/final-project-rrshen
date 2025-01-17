// Copyright (c) 2020 Rachel Shen. All rights reserved.

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/gl/gl.h>
#include <birdgame/config.h>

namespace birdgame {

// Code adapted from Snake
void PrintText(const std::string& text, const ci::Color& color,
        const ci::ivec2& size, const ci::vec2& loc, const size_t& font_size) {
  cinder::gl::color(color);

  auto box = ci::TextBox()
          .alignment(ci::TextBox::CENTER)
          .font(cinder::Font(kScoreFont, font_size))
          .size(size)
          .color(color)
          .text(text);

  const auto box_size = box.getSize();
  // Division by 2 ensures that the texture is drawn
  // At the center of the passed location
  const ci::vec2 location = {loc.x - box_size.x / 2,loc.y - box_size.y / 2};

  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, location);
}

}  // namespace birdgame
