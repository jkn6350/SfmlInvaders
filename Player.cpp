//
// Created by jakob on 22.03.26.
//

#include "Player.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "definitions.h"

Player::Player()
{
  texture_.loadFromFile("assets/player.png");
  sprite_.setTexture(texture_, true);
  sprite_.scale({PLAYER_SPRITE_SCALE_FACTOR, PLAYER_SPRITE_SCALE_FACTOR});
  sf::Vector2f starting_pos = {
    WINDOW_WIDTH - sprite_.getGlobalBounds().getSize().x / 2,
    WINDOW_HEIGHT - sprite_.getGlobalBounds().getSize().y - PLAYER_DISTANCE_TO_BOTTOM
  };
  sprite_.setPosition(starting_pos);
}

bool Player::isAlive() const noexcept
{return is_alive_;}

sf::Sprite Player::getSprite() const noexcept
{return sprite_;}

sf::FloatRect Player::getBounds() const noexcept
{return bounds_;}

void Player::handleInput()
{
  if(sf::Keyboard::isKeyPressed(KEY_A) && sprite_.getPosition().x > 0) {
    std::cout << "Moved Player Left!" << std::endl;
    sprite_.move(-PLAYER_VELOCITY, 0);
  }

  if(sf::Keyboard::isKeyPressed(KEY_D) && sprite_.getPosition().x < WINDOW_WIDTH - PLAYER_SIZE_X) {
    std::cout << "Moved Player Right!" << std::endl;
    sprite_.move(PLAYER_VELOCITY, 0);
  }

  if(sf::Keyboard::isKeyPressed(KEY_J)){
    std::cout << "Player Shot!" << std::endl;
    projectiles_.push_back(std::make_unique<Projectile>(sprite_.getPosition()));
  }
}

void Player::moveBulletsUp(sf::FloatRect bounds)
{
  for(size_t i = 0; i < projectiles_.size(); i++) {
    (*projectiles_.at(i)).rectangle_shape_.move(0, -PROJECTILE_VELOCITY);
    if (!(*projectiles_.at(i)).rectangle_shape_.getGlobalBounds().intersects(bounds))
    {
      std::cout << "Bullet erased!" << std::endl;
      projectiles_.erase(projectiles_.begin() + i);
    }
  }
}

void Player::drawBullets(sf::RenderWindow& window)
{
  for(auto& proj : projectiles_) {
    window.draw((*proj).rectangle_shape_);
  }
}

Projectile::Projectile(sf::Vector2f pos): pos_(pos)
{
  rectangle_shape_.setSize({100,200});
  rectangle_shape_.setFillColor({239, 0, 255, 1});
}
