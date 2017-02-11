#include <bits/stdc++.h>
#include "Player.h"
using namespace std;

Player::Player()
{
	this->B = new Bomb;
	this->P = new Posisi;
}

Player::Player(Bomb B)
{
	this->B = new Bomb(B);
}

Player::Player(Posisi P)
{
	this->P = new Posisi(P);
}

Player::Player(Bomb B, Posisi P)
{
	this->P = new Posisi(P);
	this->B = new Bomb(B);
}

Player::Player(const Player& P)
{
	this->P = new Posisi(P.P);
	this->B = new Bomb(P.B);
}

Player::~Player()
{
	delete this->B;
	delete this->P;
}

Player& Player::operator= (Player& P)
{
	this->B = P.B;
	this->P = P.P;
	return (*this);
}

