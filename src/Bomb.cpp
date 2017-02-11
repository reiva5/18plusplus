#include <bits/stdc++.h>
#include "Bomb.h"
#include "Point.h"
	
Bomb::Bomb()
{
	this->jarak = 0;
	this->durasi = 1;
	Point temp = Point();
	this->posisi = temp;
}
		
Bomb::Bomb(int jarak, int durasi, Point posisi)
{
	this->jarak = jarak;
	this->durasi = durasi;
	this->posisi = posisi;
}

Bomb& Bomb::operator= (Bomb& B)
{
	this->jarak = B.jarak;
	this->durasi = B.durasi;
	this->posisi = B.posisi;
	return (*this);
}
