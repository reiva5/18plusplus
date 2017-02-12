#ifndef POINT_H
#define POINT_H

class Point
{
	public:
		Point();
		Point(int x, int y);
		Point& operator= (const Point& B);
		void SetAbsis(int x);
		void SetOrdinat(int y);
		int GetAbsis();
		int GetOrdinat();

	private:
		int x;
		int y;
};

#endif