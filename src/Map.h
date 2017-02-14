#include "json.hpp"
#include "Point.h"

using json=nlohmann::json;

class Map{
	public:
		Map(); 
		Map(json&);
		~Map();
		Map& operator=(const Map&);
		Map(Map&);
		char GetElmt(int, int);
		int GetWidth();
		int GetHeight();
		bool IsBreakable(Point);
	private:
		char** elemen;
		int mapwidth;
		int mapheight;
};