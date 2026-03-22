#ifndef SFMLTEST_COIN_H
#define SFMLTEST_COIN_H
#include <cstdint>
#include <SFML/Graphics.hpp>

#define COIN_INIT_POS_Y 0
#define COIN_VELOCITY 3
#define MAX_COIN_AMOUNT 10
#define COIN_SIZE 10
#define MAX_TICKS_TILL_ALIVE 3

class Score;
class Player;

class Coin
{
private:
  sf::Vector2f pos_;
  float velocity_ = 0;
  sf::CircleShape circle_shape_;
  bool is_alive_ = false;
  int8_t ticks_until_alive_ = -1;

public:
  Coin();

  bool isInBounds();

  void resetPosition();

  void draw(sf::RenderWindow& window);


  bool trySpawn();


  void checkIfCollectedOrOutOfBounds(Player* player, Score* score);

  bool isAlive() const noexcept {return is_alive_;}
  sf::CircleShape& getSfObj() noexcept {return circle_shape_;}
  void setTicksUntilAlive(uint8_t ticks) noexcept {ticks_until_alive_ = ticks;}
  void decTicksUntilAlive() noexcept {ticks_until_alive_--;}
  int8_t getTicksUntilAlive() const noexcept {return ticks_until_alive_;}
  void setDead() noexcept {is_alive_ = false;}
  void setAlive() noexcept;
};


#endif //SFMLTEST_COIN_H