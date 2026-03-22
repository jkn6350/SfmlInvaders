#include "Coin.h"
#include "Player.h"
#include "Score.h"

#include "definitions.h"

#include <cstdlib>
#include <iostream>

Coin::Coin()
{
  pos_ = {(float)(std::rand() % WINDOW_WIDTH), (float)COIN_INIT_POS_Y};
  circle_shape_ = sf::CircleShape(COIN_SIZE);
  circle_shape_.setPosition(pos_);
}

bool Coin::isInBounds()
{
  if(pos_.y > WINDOW_HEIGHT)
    return false;

  return true;
}

void Coin::resetPosition()
{
  pos_ = {(float)(std::rand() % WINDOW_WIDTH), (float)COIN_INIT_POS_Y};
  circle_shape_.setPosition(pos_);
}

void Coin::draw(sf::RenderWindow& window)
{
  if(is_alive_)
    window.draw(circle_shape_);
}

bool Coin::trySpawn()
{
  if(ticks_until_alive_ == -1)
  {
    ticks_until_alive_ = (int8_t) rand() % MAX_TICKS_TILL_ALIVE;
    return false;
  }

  if(ticks_until_alive_ == 0) {
    is_alive_ = true;
    ticks_until_alive_ = -1;
    resetPosition();
    std::cout << "Coin spawned!" << std::endl;
    return true;
  }
  ticks_until_alive_--;
  return false;
}

void Coin::checkIfCollectedOrOutOfBounds(Player* player, Score* score)
{
  if(circle_shape_.getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
    score->increase();
    is_alive_ = false;
  }
  if(!isInBounds()) {
    setDead();
  }
}

void Coin::setAlive() noexcept
{
  is_alive_ = true;
  ticks_until_alive_ = -1;
  resetPosition();
}
