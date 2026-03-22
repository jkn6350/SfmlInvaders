#include "Score.h"

#include <cstdint>


uint16_t Score::getScore() const
{
  return coins_collected_;
}

void Score::draw(sf::RenderWindow& window)
{
  text_.setString(std::to_string(coins_collected_));
  window.draw(text_);
}

Score::Score()
{
  font_.loadFromFile(SCORE_FONT_PATH);
  text_ = sf::Text("0", font_);
}

void Score::increase()
{coins_collected_++;}
