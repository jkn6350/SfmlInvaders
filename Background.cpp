//
// Created by jakob on 22.03.26.
//

#include "Background.h"

#include "definitions.h"

Background::Background()
{
  if(!texture_.loadFromFile("/home/jakob/privat/gamedev/sfmltest/assets/background.png"))
    throw "Loading texture failed!";
  texture_.setRepeated(true);
  sprite_.setTexture(texture_);
  sprite_.setTextureRect({0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
}

sf::Sprite Background::getSprite() noexcept
{return sprite_;}

void Background::draw(sf::RenderWindow& window)
{
  window.draw(sprite_);
}

