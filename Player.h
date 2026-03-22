#ifndef SFMLINVADERS_PLAYER_H
#define SFMLINVADERS_PLAYER_H

#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#define PLAYER_VELOCITY 20
#define PLAYER_SIZE_Y 10
#define PLAYER_SIZE_X 100
#define PLAYER_SPRITE_SCALE_FACTOR 4
#define PLAYER_DISTANCE_TO_BOTTOM 25

namespace sf
{
  class RenderWindow;
}

class Projectile;

class Player
{
private:
  sf::Texture texture_;
  sf::Sprite sprite_;
  sf::FloatRect bounds_;
  float velocity_ = PLAYER_VELOCITY;
  bool is_alive_ = true;
  std::vector<std::unique_ptr<Projectile>> projectiles_;
public:
  Player();

  bool isAlive() const noexcept;
  sf::Sprite getSprite() const noexcept;
  sf::FloatRect getBounds() const noexcept;

  void handleInput();

  void moveBulletsUp(sf::FloatRect bounds);

  void drawBullets(sf::RenderWindow& window);
};

#define PROJECTILE_VELOCITY 10

class Projectile
{
  friend class Player;
private:
  sf::RectangleShape rectangle_shape_;
  sf::Vector2f pos_;
  float velocity_ = PROJECTILE_VELOCITY;
public:
  Projectile(sf::Vector2f pos);
};


#endif //SFMLINVADERS_PLAYER_H