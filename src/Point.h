#ifndef POINT_H
#define POINT_H

class Point
{
	public:
		Point();
		
		Point(int x, int y);

		Point& operator= (Point& B);

		void SetAbsis(int x);

		void SetOrdinat(int y);

		
	private:
		int x;
		int y;
};

#endif