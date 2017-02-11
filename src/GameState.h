#include <vector>
#include "Map.h"
#include "json.hpp"

using namespace std;
using json=nlohmann::json;

class GameState{
	public:
		GameState(json&);
		Map& GetMap();
	private:
		Map map;
};