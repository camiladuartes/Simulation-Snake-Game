#ifndef PLAYER_H
#define PLAYER_H
#include <iostream> // std::cin, std::cout
#include <string> // std::string
#include <fstream>
#include <utility> // std::pair
#include <vector>

using namespace std;

namespace Snake{
    /// Represents the AI engine
    class Player{
        bool find_solution();
        // Direction next_move();
    };
}
#endif