#include <iostream>
#include <fstream>
#include "GameState.h"

using namespace std;
using json=nlohmann::json;

int main(){
	ifstream json_file;
	json_file.open("../doc/state.json");
	json j;
	json_file>>j;
	json_file.close();
	
	GameState state(j);
	Map m= state.GetMap();
	for(int i=0; i<m.GetHeight(); i++){
		for(int j=0; j<m.GetWidth(); j++){
			cout<<m.GetElmt(i, j);
		}
		cout<<endl;
	}

	vector<Player> p=state.GetPlayer();
	for(int i=0; i<p.size(); i++){
		cout<<p[i].GetKey()<<endl;
	}

	vector<Bomb> b=state.GetBomb();
	for (int i=0; i<b.size(); i++){
		cout<<i<<' '<<b[i].GetOwner()<<' '<<b[i].GetPosisi().GetAbsis()<<' '<<b[i].GetPosisi().GetOrdinat()<<endl;
	}
	return 0;
}