#include <iostream>
#include <fstream>
#include "GameState.h"

using namespace std;
using json=nlohmann::json;

int main(){
	ifstream json_file;
	json_file.open("state.json");
	json j;
	json_file>>j;
	json_file.close();
	
	GameState state(j);
	state.GetMap().PrintMap();

	vector<Player> p=state.GetPlayer();
	for(int i=0; i<p.size(); i++){
		cout<<p[i].GetKey()<<endl;
	}
	return 0;
}