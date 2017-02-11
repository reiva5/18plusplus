#include "Point.h"

Point::Point()
{
	x = 0;
	y = 0;
}
		
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point& Point::operator= (Point& B)
{
	this->x = B.x;
	this->y = B.y;
}

int Point::GetAbsis(){
	return x;
}

int Point::GetOrdinat(){
	return y;
}

void Point::SetAbsis(int n){
	x=n;
}

void Point::SetOrdinat(int n){
	y=n;
}