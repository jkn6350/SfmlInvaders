//
// Created by jakob on 22.03.26.
//

#ifndef SFMLINVADERS_UI_H
#define SFMLINVADERS_UI_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/Graphics/Texture.hpp>



class Background{
private:
  sf::Texture texture_;
  sf::Sprite sprite_;
  sf::Vector2f pos_;
  float velocity_;
public:
  Background();

  sf::Sprite getSprite() noexcept;

  void draw(sf::RenderWindow& window);
};


#endif //SFMLINVADERS_UI_H