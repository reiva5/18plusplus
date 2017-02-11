#ifndef PLAYER_H
#define PLAYER_H
#include "Bomb.h"
#include "Point.h"

class Player
{
	public:
		Player();
		Player(Bomb X);
		Player(Point Y);
		Player(Bomb B, Point Y);
		Player(const Player& P);
		Player& operator= (Player& P);

		
	private:
		Bomb B;
		Point P;
};

#endif
