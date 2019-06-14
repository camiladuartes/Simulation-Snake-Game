#include <iostream>
#include "../include/snake_game.h"

int main (int argc, char *argv[]){

    Snake::Input input(argc, argv);
    
    Snake::SnakeGame game;
    
    game.initialize_game(input);
    // while(game.game_over() == false){

    //     game.update();
    //     game.render();
    // }

    return 0;
}