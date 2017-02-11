#include <bits/stdc++.h>
#include "Player.h"
using namespace std;

Player::Player(char playerKey, Point posisi, int bombBag, int bombRadius)
{
	this->playerKey = playerKey;
	this->posisi = posisi;
	this->bombBag=bombBag;
	this->bombRadius=bombRadius;
}

Player& Player::operator= (Player& P)
{
	this->playerKey = playerKey;
	this->posisi = posisi;
	this->bombBag=bombBag;
	this->bombRadius=bombRadius;
}

char Player::GetKey(){
	return playerKey;
}

