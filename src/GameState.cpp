#include "GameState.h"

using json=nlohmann::json;
using namespace std;

GameState::GameState(json& j): map(j){
	json play=j["RegisteredPlayerEntities"];
	for (auto i : play){
		string playerKey= i["Key"].get<string>();
		int x = i["Location"]["X"].get<int>();
		int y = i["Location"]["Y"].get<int>();
		Point posisi(x,y);
		int bombBag = i["BombBag"].get<int>();
		int bombRadius = i["BombRadius"].get<int>();
		Player curr_player(playerKey[0], posisi, bombBag, bombRadius);
		player.push_back(curr_player);
	}
}

Map& GameState::GetMap(){
	return map;
}

vector<Player> GameState::GetPlayer(){
	return player;
}