#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"

class Player
{
	public:
		Player(char, Point, int, int);

		char GetKey();

		Player& operator= (Player& P);

		
	private:
		char playerKey;
		Point posisi;
		int bombBag;
		int bombRadius;
};

#endif