#include <bits/stdc++.h>
#include "Player.h"
#include "Bomb.h"
#include "Point.h"
using namespace std;

Player::Player()
{
	Bomb temp = Bomb();
	this->B = temp;
}

Player::Player(Bomb B)
{
	Bomb temp = Bomb(B);
	this->B = temp;
}

Player::Player(Point P)
{
	Point temp = Point(P);
	this->P = temp;
}

Player::Player(Bomb B, Point P)
{
	Bomb temps = Bomb(B);
	Point junk = Point(P);
	this->P = junk;
	this->B = temps;
}

Player::Player(const Player& P)
{
	Bomb temps = Bomb(P.B);
	Point junk = Point(P.P);
	this->P = junk;
	this->B = temps;
}

Player& Player::operator= (Player& P)
{
	this->B = P.B;
	this->P = P.P;
	return (*this);
}

