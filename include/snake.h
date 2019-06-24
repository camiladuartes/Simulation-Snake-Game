#ifndef SNAKE_H
#define SNAKE_H

#include "snapshot.h"
#include <list>
#include <iostream>

namespace Snaze{
    //! Represents the snake and its attributes
    class Snake{
        private:

            std::pair<int,int> spawn;//!< The coordinate for spawn/respawn.
            int head_x; //<! Coordinate x of head.
            int head_y; //<! Coordinate y of head.

            int lifes; //!< Stores the amount of life of the snake.
            Directions direction; //!< The snake current direction.


            

        public: 
            std::list< std::pair<int,int> > body; //<! List of coordinates of snake body ( without head ).
            //! Constructor
            Snake(int x = 0, int y = 0, Directions d=UP )
            : lifes(5)
            {
                spawn.first = head_x = x;
                spawn.second = head_y = y;
                direction = d;
            }
            //! Set snake position in the maze.
            void set_snake_pos( int x, int y )
            {
                spawn = std::make_pair( x, y );
                head_x = x;
                head_y = y;
            }

            //! Returns the amount lives of snake.
            int get_amount_lives()const { return lifes; }
            
            //! Apply the consequences of snake death.
            void death()
            { 
                lifes--;
                head_x = spawn.first;
                head_y = spawn.second;
                if( not body.empty() )
                    body.clear();
            }

            //! Increments the snake body with the current position of head.
            void grow()
            {
                body.push_front( std::make_pair( head_x, head_y) );
            }

            //! Clear the snake body. Only the head remains.
            void shrink()
            {
                body.clear();
            }

            //! Moves the snake in the maze.
            void move( Directions d )
            {
                direction = d;
                if( direction == UP )
                {
                    if( not body.empty() )
                    {
                        body.pop_back();
                        body.push_front( std::make_pair(head_x, head_y) );
                    }
                    head_x--;
                }
                else if( direction == DOWN )
                {
                    if( not body.empty() )
                    {
                        body.pop_back();
                        body.push_front( std::make_pair(head_x, head_y) );
                    }
                    head_x++;
                }
                else if( direction == LEFT )
                {
                    if( not body.empty() )
                    {
                        body.pop_back();
                        body.push_front( std::make_pair(head_x, head_y) );
                    }
                    head_y--;
                }
                else
                {
                    if( not body.empty() )
                    {
                        body.pop_back();
                        body.push_front( std::make_pair(head_x, head_y) );
                    }
                    head_y++;
                }
            }

            //!
            Directions current_direction()const { return direction; }

            //!
            std::pair<int,int> get_head()
            {
                return std::make_pair( head_x, head_y );
            }

            //!
            //std::list< std::pair<int,int> > get_body()const { return body; }

     

    };
}//namespace
#endif