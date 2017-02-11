#ifndef BOMB_H
#define BOMB_H

#include "Point.h"

class Bomb
{
	public:
		Bomb();
		
		Bomb(int jarak, int durasi, Point posisi);

		~Bomb();

		Bomb& operator= (Bomb& B);

		
	private:
		int jarak;
		int durasi;
		Point posisi;
};

#endif