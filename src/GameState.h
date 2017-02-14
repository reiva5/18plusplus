#include <vector>
#include "Map.h"
#include "json.hpp"
#include "Player.h"
#include "Point.h"
#include "Bomb.h"

using namespace std;
using json=nlohmann::json;

class GameState
{
	public:
		GameState(json&);
		Map& GetMap();
		vector<Player> GetPlayer();
		vector<Bomb> GetBomb();
		bool in_danger(Point P);
		bool bomb_in_row(Point P);
		bool bomb_in_column(Point P);
		bool in_area(Point P, Bomb B);
		bool move_away(Point P, int& move);
		int move_BFS(Point P);
		bool get_power_up(Point P, int& move);
		bool get_wall(Point P, int&move);

	private:
		Map map;
		vector<Player> player;
		vector<Bomb> bomb;
};
