#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"

class Player
{
	public:
		Player();
		Player(char, Point, int, int);
		char GetKey();
		Player& operator= (const Player& P);
		Point GetPosisi();
		int GetBombBag();
		int GetBombRadius();
		
	private:
		char playerKey;
		Point posisi;
		int bombBag;
		int bombRadius;
};

#endif
