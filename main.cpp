// TODO separate files
// TODO 









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
#define PLAYER_SPRITE_SCALE_FACTOR 4
#define PLAYER_DISTANCE_TO_BOTTOM 25

#define COIN_INIT_POS_Y 0
#define COIN_VELOCITY 3
#define MAX_COIN_AMOUNT 10
#define COIN_SIZE 10
#define MAX_TICKS_TILL_ALIVE 3

#define SCORE_FONT_PATH "/home/jakob/privat/gamedev/sfmltest/assets/Satoshi-Bold.otf"


class Score{
private:
  sf::Text text_;
  sf::Font font_;
  uint16_t coins_collected_ = 0;

public:
  Score() {
    font_.loadFromFile(SCORE_FONT_PATH);
    text_ = sf::Text("0", font_);
  }

  void increase() {coins_collected_++;}
  uint16_t getScore() {return coins_collected_;}
  
  void draw(sf::RenderWindow& window) {
    text_.setString(std::to_string(coins_collected_));
    window.draw(text_);
  }




};

class Player
{
private:
  sf::Texture texture_;
  sf::Sprite sprite_;
  sf::FloatRect bounds_;
  sf::Vector2f pos_;
  float velocity_ = PLAYER_VELOCITY;
  bool is_alive_ = true;
public:
  Player() {
    texture_.loadFromFile("/home/jakob/privat/gamedev/sfmltest/assets/player.png");
    sprite_.setTexture(texture_, true);
    sprite_.scale({PLAYER_SPRITE_SCALE_FACTOR, PLAYER_SPRITE_SCALE_FACTOR});
    pos_ = {
      WINDOW_WIDTH - sprite_.getGlobalBounds().getSize().x / 2,
      WINDOW_HEIGHT - sprite_.getGlobalBounds().getSize().y - PLAYER_DISTANCE_TO_BOTTOM
    };
    sprite_.setPosition(pos_);
  }
  
  bool isAlive() const noexcept {return is_alive_;}
  sf::Sprite getSprite() const noexcept {return sprite_;}
  sf::FloatRect getBounds() const noexcept {return bounds_;}
  sf::Vector2f getPos() noexcept {return pos_;}
  void setPos(sf::Vector2f pos) noexcept {pos_ = pos;}

  void moveOnInput() {
    if(sf::Keyboard::isKeyPressed(KEY_A) &&
       pos_.x > 0)
    {
      pos_.x -= PLAYER_VELOCITY;
      sprite_.setPosition(pos_);
    }

    if(sf::Keyboard::isKeyPressed(KEY_D) &&
       pos_.x < WINDOW_WIDTH - PLAYER_SIZE_X) {
      
      pos_.x += PLAYER_VELOCITY;
      sprite_.setPosition(pos_);
    }
  }
};

class Coin
{
  private:
    sf::Vector2f pos_;
    float velocity_ = 0;
    sf::CircleShape circle_shape_;
    bool is_alive_ = false;
    int8_t ticks_until_alive_ = -1;

  public:
    Coin()
    {
      pos_ = {(float)(std::rand() % WINDOW_WIDTH), (float)COIN_INIT_POS_Y};
      circle_shape_ = sf::CircleShape(COIN_SIZE);
      circle_shape_.setPosition(pos_);
    }

    void moveDown()
    {
      pos_.y += COIN_VELOCITY;
      circle_shape_.setPosition(pos_);
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
      circle_shape_.setPosition(pos_);
    }

    void draw(sf::RenderWindow& window)
    {
      if(is_alive_)
        window.draw(circle_shape_);
    }


    bool trySpawn(){
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

    
    void checkIfCollectedOrOutOfBounds(Player* player, Score* score)
    {
      moveDown();

      if(circle_shape_.getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
        score->increase();
        is_alive_ = false;
      }
      if(!isInBounds()) {
        setDead();
      }
    }

    bool isAlive() const noexcept {return is_alive_;}
    sf::CircleShape getSfObj() const noexcept {return circle_shape_;}
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






int main()
{
  bool is_running;

  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Test");
  window.setFramerateLimit(30);

  std::vector<Coin *> coins_vec = {new Coin, new Coin, new Coin, new Coin, new Coin};

  Player* player = new Player;

  Score* score = new Score;
  


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
    player->moveOnInput();

    for(auto& coin : coins_vec)
    {
      bool spawned = false;
      if(coin->isAlive()){
        coin->moveDown();
        coin->checkIfCollectedOrOutOfBounds(player, score);
      } else {
        spawned = coin->trySpawn();
      }
    }


    window.clear();

    for (auto& coin : coins_vec) {
      coin->draw(window);
    }

    score->draw(window);
    
    window.draw(player->getSprite());

    window.display();
  }

  return EXIT_SUCCESS;
}