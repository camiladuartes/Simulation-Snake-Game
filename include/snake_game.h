#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "input.h"
#include "snake.h"
#include "level.h"
#include "player.h"

namespace Snake{
    /// The main entity that instantiates all other objects and manages the game execution.
    class SnakeGame{
        private:
            size_t score;
        public:
            SnakeGame()
            :score(0){}
            Level level; // initializing a new object
            Snake snake; // initializing a new object
            void initialize_game(Input input){
                level.read_file(input);
                std::cout << "\033[1;32m        ---> Welcome to the classic Snake Game <--- \033[0m\n";
                std::cout << "\033[1;32m ----------------------------------------------------------- \033[0m\n";
                std::cout << "\033[1;32m Levels loaded: \033[0m"  << "\033[1;32m"<< level.get_levels_loaded() << "\033[0m";
                std::cout << "\033[1;32m  |  Snake lives: \033[0m" << "\033[1;32m"<< snake.get_amount_lives() << "\033[0m";
                std::cout << "\033[1;32m  |  Apples to eat: \033[0m" << "\033[1;32m"<< level.get_amount_apples() << "\033[0m";
                std::cout << "\033[1;32m\n ----------------------------------------------------------- \033[0m\n";
                std::cout << "\033[1;32m >>> Press <ENTER> to start the game! \033[0m\n";
                std::cout << "\033[1;32m\n\n Lives: \033[0m";
                for(int i = 0; i < snake.get_amount_lives(); i++)
                    std::cout << "\033[1;32m"<< "♡ " << "\033[0m";
                std::cout << "\033[1;32m  |  Score:    \033[0m" << "\033[1;32m"<< score << "\033[0m";
                std::cout << "\033[1;32m  |  Food eaten: \033[0m" << "\033[1;32m"<< 10 - level.get_amount_apples() << "\033[0m" << "\033[1;32m of 10\n\033[0m";
                level.print_maze();
                std::getchar(); // For when the enter is pressed the game begins
            }
            void update(){
                
            }
            void process_events();
            void render();

            /*!
             @return True if the game is over(the snake lives ended), and False otherwise.
             */
            bool game_over(){
                if(snake.get_amount_lives() == 0){
                    return true;
                }
                return false;
            }
    };
}
#endif