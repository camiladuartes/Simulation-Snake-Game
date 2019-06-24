#ifndef PLAYER_H
#define PLAYER_H

#include "level.h"


#include <stack>
#include <deque>
#include <unordered_map>

namespace Snaze{
    //! Represents the AI engine
    class Player{
    	private:
    		std::deque<Directions> food_way_directions; //!< The sequence of moves for the player reach the objective( eat apples ). 
    		Snake ghost_snake; //<! Use for simulate the snake moves in find_solution and auxiliaries methods for verify free paths.

    	public:

    		//! returns the next move to the food( if it exists ), or to death.
    		Directions next_move( Directions current )
    		{
    			if( not food_way_directions.empty() )
    			{
	    			Directions move = food_way_directions.front();
	    			food_way_directions.pop_front(); 
	    			return move;
	    		}
	    		else
	    		{
	    			return current;
	    		}
    		}

    		//! looking for a way to food, if find, returns true, false otherwise.
        	bool find_solution( char** maze, std::pair<int,int> apple, int down_limit, int right_limit, std::pair<int,int> current_position, Snake snake )
        	{
        		food_way_directions.clear();
        		ghost_snake.shrink();
        		ghost_snake.set_snake_pos( current_position.first, current_position.second );
        		if( not snake.body.empty() )
        			ghost_snake.body = snake.body;
        		std::stack< std::pair< int,int > > lost_tails;


				std::stack<std::pair<int,int>> way;
				std::unordered_map<Snapshot::SnapshotKey,Snapshot,KeyHash, KeyEqual> album;
 
				way.push( current_position );
				int previous_move = snake.current_direction();

				while( not (way.empty()) )
				{
					Snapshot photo( current_position.first, current_position.second, NONE );
					if( go_up( current_position, maze ) and not( album[ photo.getPoseUp() ] == photo.new_pose(UP) ) and previous_move != DOWN )
					{
						previous_move = UP;

						album[ photo.getKey() ] = photo;
						current_position.first--;

						way.push( current_position );
						food_way_directions.push_back( UP );
						if( not ghost_snake.body.empty() )
						{
							lost_tails.push( ghost_snake.body.back() );
							ghost_snake.move( UP );
						}

					}
					else if( go_down( current_position, maze, down_limit ) and not(album[ photo.getPoseDown() ] == photo.new_pose(DOWN) ) and previous_move != UP )
					{
						previous_move = DOWN;

						album[ photo.getKey() ] = photo;
						current_position.first++;

						way.push( current_position );
						food_way_directions.push_back( DOWN );
						if( not ghost_snake.body.empty() )
						{
							lost_tails.push( ghost_snake.body.back() );
							ghost_snake.move( DOWN );
						}
					}
					else if( go_left( current_position, maze ) and not(album[ photo.getPoseLeft() ] == photo.new_pose(LEFT) ) and previous_move != RIGHT )
					{
						previous_move = LEFT;
					
						album[ photo.getKey() ] = photo;
						current_position.second--;

						way.push( current_position );
						food_way_directions.push_back( LEFT );
						if( not ghost_snake.body.empty() )
						{
							lost_tails.push( ghost_snake.body.back() );
							ghost_snake.move( LEFT );
						}
					}
					else if( go_right( current_position, maze, right_limit ) and not(album[ photo.getPoseRight() ] == photo.new_pose(RIGHT) ) and previous_move != LEFT )
					{
						previous_move = RIGHT;
						
						album[ photo.getKey() ] = photo;
						current_position.second++;

						way.push( current_position );
						food_way_directions.push_back( RIGHT );
						if( not ghost_snake.body.empty() )
						{
							lost_tails.push( ghost_snake.body.back() );
							ghost_snake.move( RIGHT );
						}
					}
					else 
					{
						way.pop();
						if( way.empty() )return false;
						if( not ghost_snake.body.empty() )
						{
							ghost_snake.body.pop_front();
							ghost_snake.body.push_back( lost_tails.top() );
							lost_tails.pop();
							ghost_snake.set_snake_pos( current_position.first, current_position.second );
						}
						if( not way.empty() )
							current_position = way.top();
						food_way_directions.pop_back();
						if( not food_way_directions.empty() )
							previous_move = food_way_directions.back();
						else
							previous_move = NONE;
					}
					if( way.top() == apple )
					{
						return true;
					}

				}
        	}
        	

        	//! if go up is a possible way, returns true, false otherwise.
        	bool go_up( std::pair<int,int> pos, char** & maze)
        	{
        		if( pos.first == 0)return false;
        		for( auto it = ghost_snake.body.begin(); it != ghost_snake.body.end(); ++it )
        		{
        			if( it->first == pos.first-1 and it->second == pos.second )
        				return false;
        		}
        		if( maze[pos.first-1][pos.second] == ' ' or maze[pos.first-1][pos.second] == '*' ) 
        			return true;
        		else
        			return false;
        	}

        	//! if go down is a possible way, returns true, false otherwise.
     		bool go_down( std::pair<int,int> pos, char** & maze,  int down_limit )
     		{
     			if( pos.first == down_limit )return false;
     			for( auto it = ghost_snake.body.begin(); it != ghost_snake.body.end(); ++it )
        		{
        			if( it->first == pos.first+1 and it->second == pos.second )
        				return false;
        		}
     			if( maze[pos.first+1][pos.second] == ' ' or maze[pos.first+1][pos.second] == '*') 
        			return true;
        		else 
        			return false;
     		}

     		//! if go left is a possible way, returns true, false otherwise.
        	bool go_left( std::pair<int,int> pos, char** & maze )
        	{
        		if( pos.second == 0)return false;
        		for( auto it = ghost_snake.body.begin(); it != ghost_snake.body.end(); ++it )
        		{
        			if( it->first == pos.first and it->second == pos.second-1 )
        				return false;
        		}
        		if( maze[pos.first][pos.second-1] == ' ' or maze[pos.first][pos.second-1] == '*' ) 
        			return true;
        		else 
        			return false;
        	}

        	//! if go right is a possible way, returns true, false otherwise.
        	bool go_right( std::pair<int,int> pos, char** & maze, int right_limit )
        	{
        		if( pos.second == right_limit )return false;
        		for( auto it = ghost_snake.body.begin(); it != ghost_snake.body.end(); ++it )
        		{
        			if( it->first == pos.first and it->second == pos.second+1 )
        				return false;
        		}
        		if( maze[pos.first][pos.second+1] == ' ' or maze[pos.first][pos.second+1] == '*' ) 
        			return true;
        		else 
        			return false;
        	}
    };
}//namespace
#endif