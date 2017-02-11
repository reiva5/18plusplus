#include "json.hpp"

using json=nlohmann::json;

class Map{
	public: 
		Map(json&);
		void PrintMap();
	private:
		char** elemen;
		int mapwidth;
		int mapheight;
};