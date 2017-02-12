#include <bits/stdc++.h>
#include "Player.h"
using namespace std;

Player::Player()
{
	Point pos(0,0);
	this->playerKey = 'A';
	this->posisi = pos;
	this->bombBag = 1;
	this->bombRadius = 1;
}

Player::Player(char playerKey, Point posisi, int bombBag, int bombRadius)
{
	this->playerKey = playerKey;
	this->posisi = posisi;
	this->bombBag=bombBag;
	this->bombRadius=bombRadius;
}

Player& Player::operator= (const Player& P)
{
	this->playerKey = playerKey;
	this->posisi = posisi;
	this->bombBag=bombBag;
	this->bombRadius=bombRadius;
	return (*this);
}

Point Player::GetPosisi()
{
	return posisi;
}

char Player::GetKey()
{
	return playerKey;
}

int Player::GetBombBag()
{
	return bombBag;
}

int Player::GetBombRadius()
{
	return bombRadius;
}
