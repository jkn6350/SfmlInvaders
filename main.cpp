// TODO create GameManager, add game loop and move logic out of main
// TODO rewrite projectiles
// TODO rewrite movement logic
#include "Coin.h"
#include "Player.h"
#include "Background.h"
#include "Score.h"
#include "definitions.h"

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  bool is_running;

  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Test");
  window.setFramerateLimit(30);

  std::vector<Coin *> coins_vec = {new Coin, new Coin, new Coin, new Coin, new Coin};

  Player* player = new Player;

  Score* score = new Score;

  Background* background = new Background;
  

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
          player->handleInput();
        break;

      default:
        break;
      }
    }

    player->moveBulletsUp(background->getSprite().getGlobalBounds());

    for(auto& coin : coins_vec)
    {
      bool spawned = false;
      if(coin->isAlive()){
        coin->getSfObj().move(0, COIN_VELOCITY);
        coin->checkIfCollectedOrOutOfBounds(player, score);
      } else {
        spawned = coin->trySpawn();
      }
    }


    window.clear();

    // background->draw(window);

    for (auto& coin : coins_vec) {
      coin->draw(window);
    }

    score->draw(window);
    
    window.draw(player->getSprite());

    window.display();
  }

  return EXIT_SUCCESS;
}