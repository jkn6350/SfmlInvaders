//
// Created by jakob on 22.03.26.
//

#ifndef SFMLINVADERS_SCORE_H
#define SFMLINVADERS_SCORE_H


#define SCORE_FONT_PATH "/home/jakob/privat/gamedev/sfmltest/assets/Satoshi-Bold.otf"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Score{
private:
  sf::Text text_;
  sf::Font font_;
  uint16_t coins_collected_ = 0;

public:
  Score();

  void increase();
  uint16_t getScore() const;

  void draw(sf::RenderWindow& window);
};



#endif //SFMLINVADERS_SCORE_H