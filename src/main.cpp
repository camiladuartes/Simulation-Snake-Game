#include "../include/snake_game.h"
#include<thread>
#include<chrono>

int main (int argc, char *argv[]){

    Snaze::Input input(argc, argv);
    Snaze::SnakeGame game( input );
    game.initialize_game();
    while( not game.game_over() )
    {
        game.update();
        game.render();
        std::this_thread::sleep_for(std::chrono::milliseconds( game.snake_speed() ));
    }
    return 0;
}