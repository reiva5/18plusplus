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
		bool wall_in_row(Point P1, Point P2);
		bool wall_in_column(Point P1, Point P2);
		bool in_danger(Point P);
		bool in_area(Point P, Bomb B);
		bool move_away(Point P, int& move);
		int move_BFS(Point P);
		bool get_power_up(Point P, int& move);
		bool get_wall(Point P, int&move);
		int get_near_bomb(Point P);
		bool other_in_my_reach(char playerKey, Point P, int rad);

	private:
		Map map;
		vector<Player> player;
		vector<Bomb> bomb;
};
