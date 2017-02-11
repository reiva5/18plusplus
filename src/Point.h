#ifndef POINT_H
#define POINT_H

class Point
{
	public:
		Point();
		
		Point(int x, int y);

		~Point();

		Point& operator= (Point& B);

		int GetAbsis();

		int GetOrdinat();

		void SetAbsis(int n);

		void SetOrdinat(int n);
		
	private:
		int x;
		int y;
};

#endif