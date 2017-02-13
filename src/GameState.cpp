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

bool GameState::in_danger(Point P)
{
	unsigned int i;
	bool danger = false;
	for (i = 0; i < bomb.size() && !danger; ++i)
	{
		if(bomb[i].GetPosisi().GetOrdinat()==P.GetOrdinat()){
			if((bomb[i].GetPosisi().GetAbsis()+bomb[i].GetJarak()>=P.GetAbsis())||(bomb[i].GetPosisi().GetAbsis()-bomb[i].GetJarak()<=P.GetAbsis()))
				danger=true;
		}
		else if(bomb[i].GetPosisi().GetAbsis()==P.GetAbsis()){
			if((bomb[i].GetPosisi().GetOrdinat()+bomb[i].GetJarak()>=P.GetOrdinat()) || (bomb[i].GetPosisi().GetOrdinat()-bomb[i].GetJarak()<=P.GetOrdinat()))
				danger=true;
		}
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

bool GameState::move_away(Point P, int& move){
	int min=map.GetWidth(); //potensi

	// potensi bug kalau di antara move ada dinding
	// selalu menjauh dari bomb

	for (int i=0; i<bomb.size(); i++){
		if(bomb[i].GetPosisi().GetAbsis()+bomb[i].GetJarak()>=P.GetAbsis()){
			if(bomb[i].GetPosisi().GetAbsis()+bomb[i].GetJarak()<map.GetWidth()){
				if(bomb[i].GetPosisi().GetAbsis()+bomb[i].GetJarak()-P.GetAbsis()<min){
					min=bomb[i].GetPosisi().GetAbsis()+bomb[i].GetJarak()-P.GetAbsis();
					move=3;
				}
			}
			else{
				if(map.GetWidth()-1-P.GetAbsis()<min){
					min=map.GetWidth()-1-P.GetAbsis();
					move=3;
				}
			}
		}
		else if(bomb[i].GetPosisi().GetOrdinat()+bomb[i].GetJarak()>=P.GetOrdinat()){
			if(bomb[i].GetPosisi().GetOrdinat()+bomb[i].GetJarak()<map.GetHeight()){
				if(bomb[i].GetPosisi().GetOrdinat()+bomb[i].GetJarak()-P.GetOrdinat()<min){
					min=bomb[i].GetPosisi().GetOrdinat()+bomb[i].GetJarak()-P.GetOrdinat();
					move=4;
				}
			}
			else{
				if(map.GetHeight()-1-P.GetOrdinat()<min){
					min=map.GetHeight()-1-P.GetOrdinat();
					move=4;
				}
			}
		}
	}

	// int bombMap[map.GetHeight()][map.GetWidth()];
	// for(int i=0; imap.GetHeight(); i++){
	// 	for(int j=0; j<map.GetWidth(); j++){
	// 		bombMap[i][j]=99;
	// 	}
	// }

	// for(int i=0; i<bomb.size(); i++){
	// 	Point bombPos=bomb[i].GetPosisi();
	// 	int rad=bomb[i].GetJarak();
	// 	int i=0;
	// 	while((i<=rad) && (bombPos.GetAbsis()+i<map.GetWidth())){
	// 		if((map.GetElmt(bombPos.GetOrdinat(), bombPos.GetAbsis()+i)!='#') && (map.GetElmt(bombPos.GetOrdinat(), bombPos.GetAbsis()+i)!='+')){
	// 			if(bombMap[bombPos.GetOrdinat()][bombPos.GetAbsis()+i]>bomb[i].GetDurasi()){
	// 				bombMap[bombPos.GetOrdinat()][bombPos.GetAbsis()+i]=bomb[i].GetDurasi();
	// 			}
	// 		}
	// 		else
	// 			break;
	// 		i++;
	// 	}

	// 	int i=0;
	// 	while((i<=rad) && (bombPos.GetOrdinat()+i<map.GetHeight())){
	// 		if((map.GetElmt(bombPos.GetOrdinat()+i, bombPos.GetAbsis())!='#') && (map.GetElmt(bombPos.GetOrdinat()+i, bombPos.GetAbsis())!='+')){
	// 			if(bombMap[bombPos.GetOrdinat()+i][bombPos.GetAbsis()]>bomb[i].GetDurasi()){
	// 				bombMap[bombPos.GetOrdinat()+i][bombPos.GetAbsis()]=bomb[i].GetDurasi()
	// 			}
	// 		}
	// 		else
	// 			break;
	// 		i++;
	// 	}

	// 	int i=0;
	// 	while((i<=rad) && (bombPos.GetAbsis()-i>0)){
	// 		if((map.GetElmt(bombPos.GetOrdinat(), bombPos.GetAbsis()-i)!='#') && (map.GetElmt(bombPos.GetOrdinat(), bombPos.GetAbsis()-i)!='+')){
	// 			if(bombMap[bombPos.GetOrdinat()][bombPos.GetAbsis()-i]>bomb[i].GetDurasi()){
	// 				bombMap[bombPos.GetOrdinat()][bombPos.GetAbsis()-i]=bomb[i].GetDurasi()
	// 			}
	// 		}
	// 		else
	// 			break;
	// 		i++;
	// 	}

	// 	int i=0;
	// 	while((i<=rad) && (bombPos.GetOrdinat()-i>0)){
	// 		if((map.GetElmt(bombPos.GetOrdinat()-i, bombPos.GetAbsis())!='#') && (map.GetElmt(bombPos.GetOrdinat()-i, bombPos.GetAbsis())!='+')){
	// 			if(bombMap[bombPos.GetOrdinat()-i][bombPos.GetAbsis()]>bomb[i].GetDurasi()){
	// 				bombMap[bombPos.GetOrdinat()-i][bombPos.GetAbsis()]=bomb[i].GetDurasi()
	// 			}
	// 		}
	// 		else
	// 			break;
	// 		i++;
	// 	}
	// }

	// Point playPos=P;
	// int countmove=1;
	// bool feasible=true;
	// bool safe=false;
	// while((feasible) && (!safe)){
	// 	if((playPos.GetAbsis()+countmove<map.GetWidth()) && (bombMap[playPos.GetOrdinat()][playPos.GetAbsis()+countmove]>countmove) && (map.GetElmt(playPos.GetOrdinat(), playPos.GetAbsis()+countmove)==' ')){
	// 		if(bombMap[playPos.GetOrdinat()][playPos.GetAbsis()+countmove]==99){
	// 			safe=true;
	// 		}
	// 		else
	// 			countmove++;
	// 	}
	// 	else
	// 		feasible=false;
	// }
	// if(countmove<min)
	// 	min=countmove;

	// while((feasible) && (!safe)){
	// 	if((playPos.GetAbsis()-countmove>0) && (bombMap[playPos.GetOrdinat()][playPos.GetAbsis()-countmove]>countmove) && (map.GetElmt(playPos.GetOrdinat(), playPos.GetAbsis()+countmove)==' ')){
	// 		if(bombMap[playPos.GetOrdinat()][playPos.GetAbsis()+countmove]==99){
	// 			safe=true;
	// 		}
	// 		else
	// 			countmove++;
	// 	}
	// 	else
	// 		feasible=false;
	// }
	// if(countmove<min)
	// 	min=countmove;

	
}