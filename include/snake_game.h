#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "player.h"

namespace Snaze{
    /// The main entity that instantiates all other objects and manages the game execution.
    class SnakeGame{
        private:
            size_t score;
            Level level;
            Snake snake;
            Player AI;
            bool victory;
        public:
            //! Constructor.
            SnakeGame( Input input )
            {
                victory = false;
                level.read_file(input);
                
                snake.set_snake_pos( level.spawn_pos().first, level.spawn_pos().second );
                score = 0;
                level.update_apple_location();
                AI.find_solution( level.get_characters(), level.get_apple_location(),  level.get_maze_dimensions()[level.get_current_level()].first-1, level.get_maze_dimensions()[level.get_current_level()].second-1, snake.get_head(), snake );
            }

            //! Prints a welcome message and prepare the player to game.
            void initialize_game(){
                std::cout << "\033[1;32m        ---> Welcome to the classic Snake Game <--- \033[0m\n";
                std::cout << "\033[1;32m ----------------------------------------------------------- \033[0m\n";
                std::cout << "\033[1;32m Levels loaded: \033[0m"  << "\033[1;32m"<< level.get_levels_loaded() << "\033[0m";
                std::cout << "\033[1;32m  |  Snake lives: \033[0m" << "\033[1;32m"<< snake.get_amount_lives() << "\033[0m";
                std::cout << "\033[1;32m  |  Apples to eat: \033[0m" << "\033[1;32m"<< level.get_amount_apples() << "\033[0m";
                std::cout << "\033[1;32m\n ----------------------------------------------------------- \033[0m\n";
                std::cout << "\033[1;32m >>> Press <ENTER> to start the game! \033[0m\n";
                std::cout << "\033[1;32m\n\n Lives: \033[0m";
                for(int i = 0; i < snake.get_amount_lives(); i++)
                    std::cout << "\033[1;31m"<< "♡ " << "\033[0m";
                std::cout << "\033[1;32m  |  Score:    \033[0m" << "\033[1;32m"<< score << "\033[0m";
                std::cout << "\033[1;32m  |  Food eaten: \033[0m" << "\033[1;32m"<< 10 - level.get_amount_apples() << "\033[0m" << "\033[1;32m of 10\n\033[0m";
                level.print_maze( snake );
                std::getchar(); // For when the enter is pressed the game begins
            }
            //! Render the current stage of the game.
            void render()
            {
                std::cout << "\033[1;32m        ---> Welcome to the classic Snake Game <--- \033[0m\n";
                std::cout << "\033[1;32m ----------------------------------------------------------- \033[0m\n";
                std::cout << "\033[1;32m Levels loaded: \033[0m"  << "\033[1;32m"<< level.get_levels_loaded() << "\033[0m";
                std::cout << "\033[1;32m  |  Snake lives: \033[0m" << "\033[1;32m"<< snake.get_amount_lives() << "\033[0m";
                std::cout << "\033[1;32m  |  Apples to eat: \033[0m" << "\033[1;32m"<< level.get_amount_apples() << "\033[0m";
                std::cout << "\033[1;32m\n ----------------------------------------------------------- \033[0m\n";
                std::cout << "\033[1;32m\n\n Lives: \033[0m";
                for(int i = 0; i < snake.get_amount_lives(); i++)
                    std::cout << "\033[1;31m"<< "♡ " << "\033[0m";
                std::cout << "\033[1;32m  |  Score:    \033[0m" << "\033[1;32m"<< score << "\033[0m";
                std::cout << "\033[1;32m  |  Food eaten: \033[0m" << "\033[1;32m"<< 10 - level.get_amount_apples() << "\033[0m" << "\033[1;32m of 10\n\033[0m";
                level.print_maze( snake );
            }

            //! If the player dies, a message is sent and the game is paused
            void you_die()
            {
                std::cout << "\033[1;32m  >>> YOU DIE!!! Press enter to continue " << "\033[1;32m" << std::endl;
                std::getchar();
            }


            void process_events();

            /*!
             @return True if the game is over(the snake lives ended), and False otherwise.
             */
            bool game_over(){
                if(snake.get_amount_lives() == 0){
                    std::cout << "\033[1;31m\n >>> GAME OVER!!! \033[0m\n";
                    std::cout << "\033[1;32m\n Score: \033[0m" << score << "\033[0m";
                    return true;
                }
                if( victory )
                {
                    std::cout << "\033[1;32m\n >>> CONGRATULATIONS: YOU WIN!!! \033[0m\n";
                    std::cout << "\033[1;32m\n Score: \033[0m" << score << " + " << "\033[0m";   
                    for(int i = 0; i < snake.get_amount_lives(); i++)
                    {
                        std::cout << "\033[1;31m"<< "♡" << "\033[0m";
                        score += 3000;
                    }
                    std::cout << "\033[1;32m"<< "x3000" << "\033[0m";
                    std::cout << "\033[1;32m = \033[0m" << score << "\033[0m" << std::endl;
                    return true;
                }
                return false;
            }

            //! Verify and updates the game elements.
            void update()
            {   
                score += 3*snake.body.size() + 3;
                if( level.wall( snake.get_head(), snake ) )
                {
                    snake.death();
                    AI.find_solution( level.get_characters(), level.get_apple_location(),  level.get_maze_dimensions()[level.get_current_level()].first-1, level.get_maze_dimensions()[level.get_current_level()].second-1, snake.get_head(), snake );
                    you_die();
                }
                else if( snake.get_head() == level.get_apple_location() )
                {
                    score += 1000;
                    level.update_amount_apples();
                    snake.grow();

                    if( level.get_amount_apples() == 0 )
                    {
                        if( level.get_levels_loaded()-1 == level.get_current_level() )
                        {
                            score += 10000;
                            victory = true;
                        }
                        else
                        {
                            level.next_level();
                            snake.set_snake_pos( level.spawn_pos().first, level.spawn_pos().second );
                            snake.shrink();
                        }

                    }
                    level.update_apple_location();
                    AI.find_solution( level.get_characters(), level.get_apple_location(),  level.get_maze_dimensions()[level.get_current_level()].first-1, level.get_maze_dimensions()[level.get_current_level()].second-1, snake.get_head(), snake );
                }
                snake.move( AI.next_move( snake.current_direction() ) );
            }
            //! Increases the speed of how the game is shown based on the size of the snake. 
            int snake_speed()
            {
                if( snake.body.size() < 2 )
                    return 250;
                else if( snake.body.size() < 4 )
                    return 200;
                else if( snake.body.size() < 6 )
                    return 150;
                else if( snake.body.size() < 8 )
                    return 100;
                else
                    return 50;
            }



    };
}
#endif
