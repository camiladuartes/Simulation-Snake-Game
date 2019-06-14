#ifndef LEVEL_H
#define LEVEL_H

#include <iostream> // std::cin, std::cout
#include <string> // std::string
#include <fstream>
#include <utility> // std::pair
#include <vector>

#include "input.h"

using namespace std;

namespace Snake{
    /// Represents a level of the game. It's used to print the base of the game.
    class Level{
        private:
            struct Cell{
                int x;
                int y;
                int which_carac;
            };

            std::vector<std::pair<int,int>> maze_dimensions; //!< Maze dimensions of each maze loaded.
            Cell **characters; //!< Auxiliar vector to put each maze in the `mazes_vector`.
            std::vector<Cell**> mazes_vector; // Vector with each maze stored.
            size_t levels_loaded; //!< Number of mazes in the file.
            size_t current_level; //!< Current level/maze.
            size_t amount_apples; //!< Stores the amount apples that wasn't eaten yet.
            std::pair<int,int> apple_location; //!< Stores the current apple location.
        public:
            /// Constructor
            Level()
            : amount_apples(10), levels_loaded(0), current_level(0){

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
                    characters = new Cell*[maze_dimension.first];
                    for (int i = 0; i < maze_dimension.first; ++i)
                        characters[i] = new Cell[maze_dimension.second];
                    for(int i = 0; i < maze_dimension.first; i++){
                        getline(read_file, line);
                        for(int j = 0; j < maze_dimension.second; j++){
                            characters[i][j].x = i;
                            characters[i][j].y = j;
                            characters[i][j].which_carac = line[j];
                        }
                    }
                    mazes_vector.push_back(characters);
                    levels_loaded += 1;
                }
                levels_loaded -= 1; // Because was with one more level than the real number of levels loaded.
                mazes_vector.shrink_to_fit();
                maze_dimensions.shrink_to_fit();
            }

            /// Calculates and returns randomly the new apple location attribute.
            std::pair<int,int> new_apple_location(){
                // while(true){
                //     int idx_x = rand() % maze_dimension.first;
                //     int idx_y = rand() % maze_dimension.second;
                //     if(characters[idx_x][idx_y].which_carac == ' '){
                //         apple_location.first = idx_x;
                //         apple_location.second = idx_y;
                //         return this->apple_location;
                //     }
                // }
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
            Cell** get_characters(){
                return this->characters;
            };
            /*!
            @return The current_level attibute.
            */
            size_t get_current_level(){
                return this->current_level;
            };

            /// Function to print the maze
            void print_maze(){
                if(maze_dimensions[current_level].first <= 0 || maze_dimensions[current_level].second <= 0 || maze_dimensions[current_level].first > 100 || maze_dimensions[current_level].second > 100){
                        std::cout <<"\033[1;32m Dimensions given out of bound.\n>>> GAME OVER!!!\n \033[0m";
                        std::quick_exit(1);
                    }
                std::cout << "\033[1;32m____________________________________________________________ \033[0m\n\n";
                for(int i = 0; i < maze_dimensions[current_level].first; i++){
                    for(int j = 0; j < maze_dimensions[current_level].second; j++){
                        if(mazes_vector[current_level][i][j].which_carac == '#'){
                            std::cout << "\033[1;32m▯\033[0m";
                        }
                        else if(mazes_vector[current_level][i][j].which_carac == '*'){
                            std::cout << "\033[31m▪\033[0;0m";
                            apple_location.first = i;
                            apple_location.second = j;
                        }
                        else if(mazes_vector[current_level][i][j].which_carac == '.' || mazes_vector[current_level][i][j].which_carac == ' '){
                            std::cout << " ";
                        }
                    }
                    std::cout << std::endl;
                }
                std::cout << "\033[1;32m____________________________________________________________ \033[0m\n\n";
            }

        //=== Updates the data attributes.

            /// Updates the amount of apples that wasn't eaten yet.
            size_t update_amount_apples(size_t amnt_ap){
                this->amount_apples = amnt_ap;
            };

            /// Updates the apple location
            std::pair<int,int> update_apple_location(std::pair<int,int> app_loc){
                this->apple_location = app_loc;
            };

            /// Updates the current level
            size_t update_current_level(size_t curr_lev){
                this->current_level = curr_lev;
            };
            
    };
}
#endif