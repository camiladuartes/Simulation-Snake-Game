#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <tuple>
#include <functional>

enum Directions{ UP, DOWN, LEFT, RIGHT, NONE };

struct Snapshot{
	using SnapshotKey = std::tuple < int , int , int >;
	int x;
	int y;
	int direction;

	Snapshot( int x_=0, int y_=0, int d=0)
	:x{x_}, y{y_}, direction{d}
	{ /*empty*/ }

	SnapshotKey getKey();
	SnapshotKey getPoseUp();
	SnapshotKey getPoseDown();
	SnapshotKey getPoseLeft();
	SnapshotKey getPoseRight();
	Snapshot new_pose( Directions d_ );

};

Snapshot::SnapshotKey Snapshot::getKey()
	{
		return (std::make_tuple( x, y, direction ));
	}
Snapshot::SnapshotKey Snapshot::getPoseUp()
	{
		return (std::make_tuple( x, y, UP ));
	} 
Snapshot::SnapshotKey Snapshot::getPoseDown()
	{
		return (std::make_tuple( x, y, DOWN ));
	}
Snapshot::SnapshotKey Snapshot::getPoseLeft()
	{
		return (std::make_tuple( x, y, LEFT ));
	}
Snapshot::SnapshotKey Snapshot::getPoseRight()
	{
		return (std::make_tuple( x, y, RIGHT ));
	}
Snapshot Snapshot::new_pose( Directions d_ )
{
	direction = d_;
	return *this;
}

struct KeyHash { 
	std::size_t operator()( const Snapshot::SnapshotKey& k_) const
	{
		return std::hash<int>()( std::get<0>( k_ ) ) xor ( std::hash<int>()( std::get<1>( k_ ) ) + std::hash<int>()( std::get<2>( k_ ) ));
	} 
};

struct KeyEqual {
	bool operator()( const Snapshot::SnapshotKey& lhs_ , const Snapshot::SnapshotKey& rhs_) const
	{
		return std::get<0>(lhs_) == std::get<0>(rhs_) and ( std::get<1>(lhs_) == std::get<1>(rhs_) and std::get<2>(lhs_) == std::get<2>(rhs_) );
	}

};

bool operator==( const Snapshot& lhs, const Snapshot& rhs )
{
	return lhs.x == rhs.x and lhs.y == rhs.y and lhs.direction == rhs.direction; 
}

#endif