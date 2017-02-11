#include <vector>
#include "Map.h"
#include "json.hpp"
#include "Player.h"
#include "Point.h"

using namespace std;
using json=nlohmann::json;

class GameState{
	public:
		GameState(json&);
		Map& GetMap();
		vector<Player> GetPlayer();
	private:
		Map map;
		vector<Player> player;
};