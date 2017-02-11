#include "Point.h"

Point::Point()
{
	this->x = 0;
	this->y = 0;
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
	return (*this);
}
