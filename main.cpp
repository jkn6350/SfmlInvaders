#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define KEY_ESC sf::Keyboard::Scan::Escape
#define KEY_W sf::Keyboard::Scan::W
#define KEY_A sf::Keyboard::Scan::A
#define KEY_S sf::Keyboard::Scan::S
#define KEY_D sf::Keyboard::Scan::D

#define PLAYER_VELOCITY 20
#define PLAYER_SIZE_Y 10
#define PLAYER_SIZE_X 100

#define COIN_INIT_POS_Y 0
#define COIN_VELOCITY 5
#define MAX_COIN_AMOUNT 10
#define COIN_SIZE 10
#define MAX_TICKS_TILL_ALIVE 1000

#define SCORE_FONT_PATH "/home/jakob/privat/gamedev/sfmltest/assets/Satoshi-Bold.otf"

class Coin
{
  private:
    sf::Vector2f pos_;
    float velocity_ = 0;
    sf::CircleShape sf_obj_;
    bool is_alive_ = false;
    int8_t ticks_until_alive_ = -1;

  public:
    Coin()
    {
      pos_ = {(float)(std::rand() % WINDOW_WIDTH), (float)COIN_INIT_POS_Y};
      sf_obj_ = sf::CircleShape(COIN_SIZE);
      sf_obj_.setPosition(pos_);
    }

    void moveDown()
    {
      pos_.y += COIN_VELOCITY;
      sf_obj_.setPosition(pos_);
    }

    bool isInBounds()
    {
      if(pos_.y > WINDOW_HEIGHT)
        return false;
      
      return true;
    }

    void resetPosition()
    {
      pos_ = {(float)(std::rand() % WINDOW_WIDTH), (float)COIN_INIT_POS_Y};
      sf_obj_.setPosition(pos_);
    }

    void draw(sf::RenderWindow& window)
    {
      if(is_alive_)
        window.draw(sf_obj_);
    }

    bool isAlive() const noexcept {return is_alive_;}
    sf::CircleShape getSfObj() const noexcept {return sf_obj_;}
    void setTicksUntilAlive(uint8_t ticks) noexcept {ticks_until_alive_ = ticks;}
    void decTicksUntilAlive() noexcept {ticks_until_alive_--;}
    int8_t getTicksUntilAlive() const noexcept {return ticks_until_alive_;}
    void setDead() noexcept {is_alive_ = false;}
    void setAlive() noexcept {
      is_alive_ = true;
      ticks_until_alive_ = -1;
      resetPosition();
    }
};

class Score{
private:
  sf::Text text_obj_;
  sf::Font font_obj_;
  uint16_t coins_collected_ = 0;

public:
  Score() {
    font_obj_.loadFromFile(SCORE_FONT_PATH);
    text_obj_ = sf::Text("0", font_obj_);
  }

  void increase() {coins_collected_++;}
  uint16_t getScore() {return coins_collected_;}
  
  void draw(sf::RenderWindow& window) {
    text_obj_.setString(std::to_string(coins_collected_));
    window.draw(text_obj_);
  }




};


int main()
{
  bool is_running;

  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Test");
  window.setFramerateLimit(30);

  std::vector<Coin *> coins_vec = {new Coin, new Coin, new Coin, new Coin, new Coin};

  sf::RectangleShape player({PLAYER_SIZE_X, PLAYER_SIZE_Y});
  sf::Vector2f player_pos((WINDOW_WIDTH - PLAYER_SIZE_X / 2), WINDOW_HEIGHT - PLAYER_SIZE_Y);
  player.setPosition(player_pos);

  Score player_score;


  while(window.isOpen()) {
    sf::Event event;
    
    while(window.pollEvent(event)) {
      switch (event.type){
        case sf::Event::Closed:
          window.close();
          break;
        
        case sf::Event::KeyPressed:
          if(event.key.scancode == KEY_ESC)
            window.close();
        break;

      default:
        break;
      }
    }

    for (auto& coin : coins_vec) {
      if(coin->isAlive()) {
        coin->moveDown();

        if(coin->getSfObj().getGlobalBounds().intersects(player.getGlobalBounds())) {
          player_score.increase();
          coin->setDead();
        }
        if(!coin->isInBounds()) {
          coin->setDead();
        }
      } else {
        if(coin->getTicksUntilAlive() == -1)
        {
          coin->setTicksUntilAlive(uint8_t(rand() % MAX_TICKS_TILL_ALIVE));
          continue;
        }
        
        if(coin->getTicksUntilAlive() == 0) {
          coin->setAlive();
          std::cout << "Coin spawned!" << std::endl;
          continue;
        }
        coin->decTicksUntilAlive();
      }
    }

    // move player with wasd
    // if(sf::Keyboard::isKeyPressed(KEY_W) &&
    //    player_pos.y > 0)
    // {
    //   player_pos.y -= PLAYER_VELOCITY;
    //   player.setPosition(player_pos);
    // }
    if(sf::Keyboard::isKeyPressed(KEY_A) &&
       player_pos.x > 0)
    {
      player_pos.x -= PLAYER_VELOCITY;
      player.setPosition(player_pos);
    }
    // if(sf::Keyboard::isKeyPressed(KEY_S) &&
    //    player_pos.y < WINDOW_HEIGHT - PLAYER_SIZE_Y)
    // {
    //   player_pos.y += PLAYER_VELOCITY;
    //   player.setPosition(player_pos);
    // }
    if(sf::Keyboard::isKeyPressed(KEY_D) &&
       player_pos.x < WINDOW_WIDTH - PLAYER_SIZE_X) {
      
      player_pos.x += PLAYER_VELOCITY;
      player.setPosition(player_pos);
    }




    window.clear();

    for (auto& coin : coins_vec) {
      coin->draw(window);
    }

    player_score.draw(window);
    
    window.draw(player);

    window.display();
  }

  return EXIT_SUCCESS;
}