#include <bits/stdc++.h>
#include "GameState.h"

using json=nlohmann::json;
using namespace std;

GameState::GameState(json& j): map(j)
{
	json play=j["RegisteredPlayerEntities"];
	for (auto i : play)
	{
		string playerKey= i["Key"].get<string>();
		int x = i["Location"]["X"].get<int>()-1;
		int y = i["Location"]["Y"].get<int>()-1;
		Point posisi(x,y);
		int bombBag = i["BombBag"].get<int>();
		int bombRadius = i["BombRadius"].get<int>();
		Player curr_player(playerKey[0], posisi, bombBag, bombRadius);
		player.push_back(curr_player);
	}

	json b=j["GameBlocks"];
	for(auto k: b)
	{
		for (auto i : k)
		{
			if(i["Bomb"]!=NULL)
			{
				int jarak= i["Bomb"]["BombRadius"].get<int>();
				int durasi= i["Bomb"]["BombTimer"].get<int>();
				int x=i["Bomb"]["Location"]["X"].get<int>()-1;
				int y=i["Bomb"]["Location"]["Y"].get<int>()-1;
				Point posisi(x,y);
				string owner=i["Bomb"]["Owner"]["Key"].get<string>();
				Bomb curr_bomb(jarak, durasi, posisi, owner[0]);
				bomb.push_back(curr_bomb);
			}
		}
	}
}

Map& GameState::GetMap()
{
	return map;
}

vector<Player> GameState::GetPlayer()
{
	return player;
}

vector<Bomb> GameState::GetBomb()
{
	return bomb;
}

bool GameState::in_danger ()
{
	unsigned int i;
	bool danger = false;
	for (i = 0; i < bomb.size() && !danger; ++i)
	{
		
	}
	return danger;
}

bool GameState::bomb_in_row(Point P)
{
	bool cek;
	int i = 0;
	Point Ptemp;
	cek = false;
	while(i < bomb.size() && !cek)
	{
		cek = in_area(P,bomb[i]);
		i++;
	}
	return cek;
}

bool GameState::bomb_in_column(Point P)
{
	bool cek = false;
	int i = 0;
	Point Ptemp;
	while(i < bomb.size() && !cek)
	{
		Ptemp = bomb[i].GetPosisi();
		if(P.GetOrdinat() == Ptemp.GetOrdinat())
		{
			cek = true;
		}
		i++;
	}
	return cek;
}

bool GameState::in_area(Point P, Bomb B)
{
	Point Ptemp = B.GetPosisi();
	bool cekX = false;
	bool cekY = false;
	int batas1,batas2;

	batas1 = Ptemp.GetAbsis() + B.GetJarak();
	batas2 = Ptemp.GetAbsis() - B.GetJarak();
	if(P.GetAbsis() >= batas2 && P.GetAbsis() <= batas1)
	{
		cekX=true;
	}
	batas1 = Ptemp.GetOrdinat() + B.GetJarak();
	batas2 = Ptemp.GetOrdinat() - B.GetJarak();
	if(P.GetOrdinat() >= batas2 && P.GetOrdinat() <= batas1)
	{
		cekY = true;
	}

	return (cekY && cekX);
}
