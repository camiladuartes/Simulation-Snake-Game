#ifndef SNAKE_H
#define SNAKE_H

#include <iostream> // std::cin, std::cout
#include <string> // std::string
#include <fstream>
#include <utility> // std::pair
#include <vector>

using namespace std;

namespace Snake{
    /// Represents the snake and its attributes
    class Snake{
        private:
            size_t amount_lives; //!< Stores the amount of life of the snake
            size_t lenght; //!< Stores the snake lenght.
        public:
            /// Constructor
            Snake()
            : amount_lives(5){

            }
            /*!
            @return The amount_lives attibute.
            */
            size_t get_amount_lives(){
                return this->amount_lives;
            };

            /*!
            @return The lenght attibute.
            */
            size_t get_lenght(){
                return this->lenght;
            };
        //=== Updates the data attributes.
            /// Updates the amount of lives.
            size_t update_amount_lives(size_t amt_liv){
                this->amount_lives = amt_liv;
            };
            /// Updates de snake lenght
            size_t update_lenght(size_t lgt){
                this->lenght = lgt;
            }
    };
}
#endif