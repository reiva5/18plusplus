#include <vector>
#include "Map.h"
#include "json.hpp"
#include "Player.h"
#include "Point.h"
#include "Bomb.h"

using namespace std;
using json=nlohmann::json;

class GameState{
	public:
		GameState(json&);
		Map& GetMap();
		vector<Player> GetPlayer();
		vector<Bomb> GetBomb();
		bool in_danger (Point P);
		bool bomb_in_row(Point P);
		bool bomb_in_coloum(Point P);
		bool in_area(Point P, Bomb B);

	private:
		Map map;
		vector<Player> player;
		vector<Bomb> bomb;
};