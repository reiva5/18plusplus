#include "Map.h"
#include <iostream>

using namespace std;
using json=nlohmann::json;

Map::Map(json& j){
	mapwidth=j["MapWidth"].get<int>();
	mapheight=j["MapHeight"].get<int>();

	elemen = new char*[mapheight];
	for(int i=0; i<mapwidth; i++){
		elemen[i]= new char[mapwidth];
	}

	json gameBlocks=j["GameBlocks"];
	for (auto i : gameBlocks){
		for (auto k : i){
			if(k["Bomb"]!=NULL)
					elemen[k["Location"]["Y"].get<int>()-1][k["Location"]["X"].get<int>()-1]='0';
			else if(k["Entity"]["$type"]==NULL){
				if(k["PowerUp"]!=NULL)
					elemen[k["Location"]["Y"].get<int>()-1][k["Location"]["X"].get<int>()-1]='!';
				else
					elemen[k["Location"]["Y"].get<int>()-1][k["Location"]["X"].get<int>()-1]=' ';
			}
			else if(k["Entity"]["$type"]=="Domain.Entities.IndestructibleWallEntity, Domain"){
				elemen[k["Location"]["Y"].get<int>()-1][k["Location"]["X"].get<int>()-1]='#';
			}
			else if(k["Entity"]["$type"]=="Domain.Entities.DestructibleWallEntity, Domain")
				elemen[k["Location"]["Y"].get<int>()-1][k["Location"]["X"].get<int>()-1]='+';
		}
	}
}

void Map::PrintMap(){
	for(int i=0; i<mapheight; i++){
		for(int j=0; j<mapwidth; j++){
			cout<<elemen[i][j];
		}
		cout<<endl;
	}
}