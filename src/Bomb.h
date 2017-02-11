#ifndef BOMB_H
#define BOMB_H

#include "Point.h"

class Bomb
{
	public:
		Bomb();
		
		Bomb(int jarak, int durasi, Point posisi);

		Bomb& operator= (Bomb& B);

		int GetJarak();

		int GetDurasi();

		Point GetPosisi();

		void SetDuration(int n);

	private:
		int jarak;
		int durasi;
		Point posisi;
};

#endif