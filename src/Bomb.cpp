#include <bits/stdc++.h>
#include "Bomb.h"
#include "Point.h"
	
Bomb::Bomb()
{
	this->jarak = 0;
	this->durasi = 1;
<<<<<<< HEAD
	Point temp = Point();
	this->posisi = temp;
=======
	this->posisi.SetAbsis(0);
	this->posisi.SetOrdinat(0);
>>>>>>> d285b4fb42e184cc9cc88b372358b9e9fb39e528
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
<<<<<<< HEAD
	return (*this);
}
=======
}
int Bomb::GetJarak(){
	return this->jarak;
}

int Bomb::GetDurasi(){
	return this->durasi;
}

Point Bomb::GetPosisi(){
	return this->posisi;
}

void Bomb::SetDuration(int n){
	this->durasi=n;
}
>>>>>>> d285b4fb42e184cc9cc88b372358b9e9fb39e528
