#ifndef SNAKE_H
#define SNAKE_H

#include "snapshot.h"
#include <list>
#include <iostream>

namespace Snaze{
    //! Represents the snake and its attributes
    class Snake{
        private:

            std::pair<int,int> spawn;
            int head_x;
            int head_y;

            int lifes; //!< Stores the amount of life of the snake
            Directions direction;


            

        public:
            std::list< std::pair<int,int> > body;
            //! Constructor
            Snake(int x = 0, int y = 0, Directions d=UP )
            : lifes(5)
            {
                spawn.first = head_x = x;
                spawn.second = head_y = y;
                direction = d;
            }

            void set_snake_pos( int x, int y )
            {
                spawn = std::make_pair( x, y );
                head_x = x;
                head_y = y;
            }

            //!
            int get_amount_lives()const { return lifes; }
            
            //!
            void death()
            { 
                lifes--;
                head_x = spawn.first;
                head_y = spawn.second;
                if( not body.empty() )
                    body.clear();
            }

            //! 
            void grow()
            {
                body.push_front( std::make_pair( head_x, head_y) );
            }

            //!
            void shrink()
            {
                body.clear();
            }

            //!
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