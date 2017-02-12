#include "json.hpp"

using json=nlohmann::json;

class Map{
	public:
		Map(); 
		Map(json&);
		~Map();
		Map& operator=(Map&);
		Map(Map&);
		char GetElmt(int, int);
		int GetWidth();
		int GetHeight();
	private:
		char** elemen;
		int mapwidth;
		int mapheight;
};