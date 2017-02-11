#include "GameState.h"
#include <fstream>

using json=nlohmann::json;
using namespace std;

GameState::GameState(json& j): map(j){
}

Map& GameState::GetMap(){
	return map;
}