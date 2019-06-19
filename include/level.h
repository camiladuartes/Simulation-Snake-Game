#ifndef LEVEL_H
#define LEVEL_H

#include <iostream> // std::cin, std::cout
#include <vector>
#include <fstream>

#include "input.h"
#include "snake.h"

namespace Snaze{
    /// Represents a level of the game. It's used to print the base of the game.
    class Level{
        private:

            std::vector<std::pair<int,int>> maze_dimensions; //!< Maze dimensions of each maze loaded.
            std::vector<char**> mazes_vector; // Vector with each maze stored.
            size_t levels_loaded; //!< Number of mazes in the file.
            size_t current_level; //!< Current level/maze.
            size_t amount_apples; //!< Stores the amount apples that wasn't eaten yet.
            std::pair<int,int> apple_location; //!< Stores the current apple location.

            std::vector<std::pair<int,int>> snake_spawn;
        public:
            /// Constructor
            Level()
            : amount_apples(10), levels_loaded(0), current_level(0){

            }
            //! destructor
            ~Level()
            {
                for( int i = 0; i < levels_loaded; i++ )
                {
                    for( int j = 0; j < maze_dimensions[i].first; j++ )
                        delete[] mazes_vector[i][j];
                    delete[] mazes_vector[i];
                }

            }

            /// Reads the file and stores the maze in the martix, and the maze_dimensions too.
            void read_file(Input input){
                std::ifstream read_file;
                read_file.open(input.get_file_name());
                if(!read_file){
                        std::cout << "\033[1;32m Could not open the file.\n>>> GAME OVER!!!\n \033[0m";
                        std::quick_exit(1);
                }
                while(!read_file.eof())
                {
                    std::string line; // will receive each line of the file
                    std::pair<int,int> maze_dimension;
                    read_file >> maze_dimension.first >> maze_dimension.second;
                    read_file.ignore();
                    maze_dimensions.push_back(maze_dimension);
                    char** characters = new char*[maze_dimension.first];
                    for (int i = 0; i < maze_dimension.first; ++i)
                        characters[i] = new char[maze_dimension.second];
                    for(int i = 0; i < maze_dimension.first; i++){
                        getline(read_file, line);
                        for(int j = 0; j < maze_dimension.second; j++){
                            characters[i][j] = line[j];
                            if( line[j] == '*')
                            {
                                snake_spawn.push_back( std::make_pair(i,j) );
                            }
                        }
                    }
                    mazes_vector.push_back(characters);
                    levels_loaded += 1;
                }
                levels_loaded -= 1; // Because was with one more level than the real number of levels loaded.
                mazes_vector.shrink_to_fit();
                maze_dimensions.shrink_to_fit();
                snake_spawn.shrink_to_fit();
                read_file.close();
            }

            //!
            void update_apple_location(){
                //
                 while(true){
                     int idx_x = rand() % (maze_dimensions[current_level].first-1);
                     int idx_y = rand() % (maze_dimensions[current_level].second-1);
                     if(mazes_vector[current_level][idx_x][idx_y] == ' '){
                         apple_location.first = idx_x;
                         apple_location.second = idx_y;
                         break;
                     }
                 }
            }

            /*!
            @return The maze_dimension attibute.
            */
            std::vector<std::pair<int,int>> get_maze_dimensions(){
                return this->maze_dimensions;
            };
            /*!
            @return The amount_apples attibute.
            */
            size_t get_amount_apples(){
                return this->amount_apples;
            };
            /*!
            @return The apple_location attibute.
            */
            std::pair<int,int> get_apple_location(){
                return this->apple_location;
            };
            /*!
            @return The levels_loaded attibute.
            */
            size_t get_levels_loaded(){
                return this->levels_loaded;
            };
            /*!
            @return The characters attibute.
            */
            char** get_characters(){
                return mazes_vector[current_level];
            };
            /*!
            @return The current_level attibute.
            */
            size_t get_current_level(){
                return this->current_level;
            };

            /// Function to print the maze
            void print_maze( Snake snake ){
                if(maze_dimensions[current_level].first <= 0 || maze_dimensions[current_level].second <= 0 || maze_dimensions[current_level].first > 100 || maze_dimensions[current_level].second > 100){
                        std::cout <<"\033[1;32m Dimensions given out of bound.\n>>> GAME OVER!!!\n \033[0m";
                        std::quick_exit(1);
                    }
                std::cout << "\033[1;32m____________________________________________________________ \033[0m\n\n";
                for(int i = 0; i < maze_dimensions[current_level].first; i++){
                    for(int j = 0; j < maze_dimensions[current_level].second; j++){
                        bool jump = false;
                        if( snake.get_head().first == i and snake.get_head().second == j )
                        {
                            if( snake.current_direction() == UP )
<<<<<<< HEAD
                                std::cout << "\033[1;36m▴\033[0m";
                            else if( snake.current_direction() == DOWN )
                                std::cout << "\033[1;36m▾\033[0m";
                            else if( snake.current_direction() == LEFT )
                                std::cout << "\033[1;36m◂\033[0m";
                            else 
                                std::cout << "\033[1;36m▸\033[0m";
=======
                                std::cout << "V";
                            else if( snake.current_direction() == DOWN )
                                std::cout << "A";
                            else if( snake.current_direction() == LEFT )
                                std::cout << ">";
                            else 
                                std::cout << "<";
>>>>>>> 47b3168bd2c4a571b393a0bf49ec104e27419595
                            continue;
                        }
                        else
                        {
                            if( not snake.body.empty() )
                            {
                                for( auto it = snake.body.begin(); it != snake.body.end(); it++ )
                                {
                                    if( it->first == i and it->second == j )
                                    {
<<<<<<< HEAD
                                        std::cout << "\033[1;36m⬧\033[0m";
=======
                                        std::cout << "o";
>>>>>>> 47b3168bd2c4a571b393a0bf49ec104e27419595
                                        jump = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if( not jump )
                        {
                            if( apple_location.first == i and apple_location.second == j )
                            {
<<<<<<< HEAD
                                std::cout << "\033[31m▪\033[0;0m";
=======
                                std::cout << "X";
>>>>>>> 47b3168bd2c4a571b393a0bf49ec104e27419595
                            }
                            else if(mazes_vector[current_level][i][j] == '#'){
                                std::cout << "\033[1;32m▯\033[0m";
                            }
<<<<<<< HEAD
                            else if(mazes_vector[current_level][i][j] == '.' || mazes_vector[current_level][i][j] == ' ' || mazes_vector[current_level][i][j] == '*'){
=======
                            else if(mazes_vector[current_level][i][j] == '*'){
                                std::cout << "\033[31m▪\033[0;0m";
                            }
                            else if(mazes_vector[current_level][i][j] == '.' || mazes_vector[current_level][i][j] == ' '){
>>>>>>> 47b3168bd2c4a571b393a0bf49ec104e27419595
                                std::cout << " ";
                            }
                        }
                    }
                    std::cout << std::endl;
                }
                std::cout << "\033[1;32m____________________________________________________________ \033[0m\n\n";
            }

        //=== Updates the data attributes.

            /// Updates the amount of apples that wasn't eaten yet.
            void update_amount_apples(){
                amount_apples--;
            };

            /// Updates the current level
            void next_level(){
                current_level++;
                amount_apples = 10;
                std::cout << "\033[1;32m  |  Level complete press enter to continue " << "\033[1;32m" << std::endl;
                getchar();
                
            };
            

            std::pair<int,int> spawn_pos()
            {
                return snake_spawn[current_level];
            }

            bool wall( std::pair<int,int> pos, Snake snake )
            {
                if( mazes_vector[current_level][pos.first][pos.second] == '#' or mazes_vector[current_level][pos.first][pos.second] == '.' )
                    return true;
                else 
                    for( auto it = snake.body.begin(); it != snake.body.end(); it++ )
                        if( it->first == pos.first and it->second == pos.second )
                            return true;
                return false;
            }
    };
}//spacename
#endif
