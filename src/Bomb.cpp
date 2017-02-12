#include <bits/stdc++.h>
#include "Bomb.h"
#include "Point.h"
	
Bomb::Bomb()
{
	this->jarak = 0;
	this->durasi = 1;
	Point temp = Point();
	this->posisi = temp;
	this->posisi.SetAbsis(0);
	this->posisi.SetOrdinat(0);
	this->owner='0';
}
		
Bomb::Bomb(int jarak, int durasi, Point posisi, char owner)
{
	this->jarak = jarak;
	this->durasi = durasi;
	this->posisi = posisi;
	this->owner=owner;
}

Bomb& Bomb::operator= (Bomb& B)
{
	this->jarak = B.jarak;
	this->durasi = B.durasi;
	this->posisi = B.posisi;
	return (*this);
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

char Bomb::GetOwner(){
	return owner;
}