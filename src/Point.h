#ifndef POINT_H
#define POINT_H

class Point
{
	public:
		Point();
		
		Point(int x, int y);

		~Point();

		Point& operator= (Point& B);

		
	private:
		int x;
		int y;
};

#endif