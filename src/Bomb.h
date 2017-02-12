#ifndef BOMB_H
#define BOMB_H

#include "Point.h"

class Bomb
{
	public:
		Bomb();
		
		Bomb(int jarak, int durasi, Point posisi, char owner);

		Bomb& operator= (Bomb& B);

		int GetJarak();

		int GetDurasi();

		Point GetPosisi();

		void SetDuration(int n);

		char GetOwner();

	private:
		int jarak;
		int durasi;
		Point posisi;
		char owner;
};

#endif