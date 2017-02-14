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

bool GameState::wall_in_row(Point P1, Point P2)
{
	bool found=false;
	int i = 0;
	if (P1.GetAbsis() > P2.GetAbsis())
	{
		for (i = P1.GetAbsis(); i >= P2.GetAbsis() && (!found); --i)
		{
			if (map.GetElmt(P1.GetOrdinat(),i) == '+' || map.GetElmt(P2.GetOrdinat(),i) == '#')
			{
				found = true;
			}
		}
	}

	else
	{
		for (i = P1.GetAbsis(); i <= P2.GetAbsis() && (!found); ++i)
		{
			if (map.GetElmt(P1.GetOrdinat(),i) == '+' || map.GetElmt(P1.GetOrdinat(),i) == '#')
			{
				found=true;
			}
		}
	}
	return found;
}

bool GameState::wall_in_column(Point P1, Point P2)
{
	bool cek = false;
	int j = 0;
	if (P1.GetOrdinat() > P2.GetOrdinat())
	{
		for (j = P1.GetOrdinat(); j >= P2.GetOrdinat() && (!cek); --j)
		{
			if (map.GetElmt(j,P1.GetAbsis()) == '+' || map.GetElmt(j,P1.GetAbsis()) == '#')
			{
				cek=true;
			}
		}
	}

	else
	{
		for (j = P1.GetOrdinat(); j >= P2.GetOrdinat() && (!cek); --j)
		{
			if (map.GetElmt(j,P1.GetAbsis()) == '+' || map.GetElmt(j,P1.GetAbsis()) == '#')
			{
				cek=true;
			}
		}
	}
	return cek;
}

bool GameState::in_danger(Point P)
{
	// KAMUS LOKAL
	unsigned int i, j;
	bool danger = false;
	bool found = false;

	// ALGORITMA
	for (i = 0; i < bomb.size() && !danger; ++i)
	{
		// Pengecekan bomb berada satu ordinat 
		if (bomb[i].GetPosisi().GetOrdinat() == P.GetOrdinat())
		{
			// Pengecekan radius bomb kurang dari jarak player ke bomb berdasarkan absis
			if (abs(bomb[i].GetPosisi().GetAbsis() - P.GetAbsis()) <= bomb[i].GetJarak())
			{
				danger= (!wall_in_row(bomb[i].GetPosisi(), P));
			}
		}

		// Pengecekan bomb berada satu absis
		else if (bomb[i].GetPosisi().GetAbsis() == P.GetAbsis())
		{
			// Pengecekan radius bomb kurang dari jarak player ke bomb berdasarkan ordinat
			if (abs(bomb[i].GetPosisi().GetOrdinat() - P.GetOrdinat()) <= bomb[i].GetJarak())
			{
				danger= (!wall_in_column(bomb[i].GetPosisi(), P));
			}
		}
	}

	return danger;
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
	int min=map.GetWidth(); 
	int bombMap[map.GetHeight()][map.GetWidth()];

	for(int i=0; i<map.GetHeight(); i++){
		for(int j=0; j<map.GetWidth(); j++){
			bombMap[i][j]=99;
		}
	}

	for(int j=0; j<bomb.size(); j++){
		Point bombPos=bomb[j].GetPosisi();
		int rad=bomb[j].GetJarak();
		int i=0;
		while((i<=rad) && (bombPos.GetAbsis()+i<map.GetWidth())){
			if((map.GetElmt(bombPos.GetOrdinat(), bombPos.GetAbsis()+i)!='#') && (map.GetElmt(bombPos.GetOrdinat(), bombPos.GetAbsis()+i)!='+')){
				if(bombMap[bombPos.GetOrdinat()][bombPos.GetAbsis()+i]>bomb[j].GetDurasi()){
					bombMap[bombPos.GetOrdinat()][bombPos.GetAbsis()+i]=bomb[j].GetDurasi();
				}
			}
			else
				break;
			i++;
		}

		i=0;
		while((i<=rad) && (bombPos.GetOrdinat()+i<map.GetHeight())){
			if((map.GetElmt(bombPos.GetOrdinat()+i, bombPos.GetAbsis())!='#') && (map.GetElmt(bombPos.GetOrdinat()+i, bombPos.GetAbsis())!='+')){
				if(bombMap[bombPos.GetOrdinat()+i][bombPos.GetAbsis()]>bomb[j].GetDurasi()){
					bombMap[bombPos.GetOrdinat()+i][bombPos.GetAbsis()]=bomb[j].GetDurasi();
				}
			}
			else
				break;
			i++;
		}

		i=0;
		while((i<=rad) && (bombPos.GetAbsis()-i>0)){
			if((map.GetElmt(bombPos.GetOrdinat(), bombPos.GetAbsis()-i)!='#') && (map.GetElmt(bombPos.GetOrdinat(), bombPos.GetAbsis()-i)!='+')){
				if(bombMap[bombPos.GetOrdinat()][bombPos.GetAbsis()-i]>bomb[j].GetDurasi()){
					bombMap[bombPos.GetOrdinat()][bombPos.GetAbsis()-i]=bomb[j].GetDurasi();
				}
			}
			else
				break;
			i++;
		}

		i=0;
		while((i<=rad) && (bombPos.GetOrdinat()-i>0)){
			if((map.GetElmt(bombPos.GetOrdinat()-i, bombPos.GetAbsis())!='#') && (map.GetElmt(bombPos.GetOrdinat()-i, bombPos.GetAbsis())!='+')){
				if(bombMap[bombPos.GetOrdinat()-i][bombPos.GetAbsis()]>bomb[j].GetDurasi()){
					bombMap[bombPos.GetOrdinat()-i][bombPos.GetAbsis()]=bomb[j].GetDurasi();
				}
			}
			else
				break;
			i++;
		}
	}

	for(int i=0; i<map.GetHeight(); i++){
		for(int j=0; j<map.GetWidth(); j++){
			cout<<bombMap[i][j]<<' ';
		}
		cout<<endl;
	}

	int mv;
	Point playPos=P;
	int countmove=1;
	bool feasible=true;
	bool safe=false;
	while((feasible) && (!safe)){
		if((playPos.GetAbsis()+countmove<map.GetWidth()) && (bombMap[playPos.GetOrdinat()][playPos.GetAbsis()+countmove]>countmove) && 
			(map.GetElmt(playPos.GetOrdinat(), playPos.GetAbsis()+countmove)!='#') && (map.GetElmt(playPos.GetOrdinat(), playPos.GetAbsis()+countmove)!='+')){
			if(bombMap[playPos.GetOrdinat()][playPos.GetAbsis()+countmove]==99){
				safe=true;
			}
			else if((map.GetElmt(playPos.GetOrdinat()-1, playPos.GetAbsis()+countmove)!='#') && (map.GetElmt(playPos.GetOrdinat()-1, playPos.GetAbsis()+countmove)!='+')
				&& (bombMap[playPos.GetOrdinat()-1][playPos.GetAbsis()+countmove]==99)){
				safe=true;
				countmove++;
			}
			else if((map.GetElmt(playPos.GetOrdinat()+1, playPos.GetAbsis()+countmove)!='#') && (map.GetElmt(playPos.GetOrdinat()+1, playPos.GetAbsis()+countmove)!='+')
				&& (bombMap[playPos.GetOrdinat()+1][playPos.GetAbsis()+countmove]==99)){
				safe=true;
				countmove++;
			}
			else
				countmove++;
		}
		else if( (bombMap[playPos.GetOrdinat()][playPos.GetAbsis()+countmove]<countmove))
			safe=true;
		else
			feasible=false;
	}
	if(safe && (countmove<min)){
		min=countmove;
		mv=3;
	}
	else
		cout<<"cant right"<<endl;

	countmove=1;
	feasible=true;
	safe=false;
	while((feasible) && (!safe)){
		if((playPos.GetOrdinat()+countmove<map.GetHeight()) && (bombMap[playPos.GetOrdinat()+countmove][playPos.GetAbsis()]>countmove) && 
			(map.GetElmt(playPos.GetOrdinat()+countmove, playPos.GetAbsis())!='#') && (map.GetElmt(playPos.GetOrdinat()+countmove, playPos.GetAbsis())!='+')){
			if(bombMap[playPos.GetOrdinat()+countmove][playPos.GetAbsis()]==99){
				safe=true;
			}
			else if((map.GetElmt(playPos.GetOrdinat()+countmove, playPos.GetAbsis()-1)!='#') && (map.GetElmt(playPos.GetOrdinat()+countmove, playPos.GetAbsis()-1)!='+')
				&& (bombMap[playPos.GetOrdinat()+countmove][playPos.GetAbsis()-1]==99)){
				safe=true;
				countmove++;
			}
			else if((map.GetElmt(playPos.GetOrdinat()+countmove, playPos.GetAbsis()+1)!='#') && (map.GetElmt(playPos.GetOrdinat()+countmove, playPos.GetAbsis()+1)!='+')
				&& (bombMap[playPos.GetOrdinat()+countmove][playPos.GetAbsis()+1]==99)){
				safe=true;
				countmove++;
			}
			else
				countmove++;
		}
		else if( (bombMap[playPos.GetOrdinat()+countmove][playPos.GetAbsis()]<countmove))
			safe=true;
		else
			feasible=false;
	}
	if(safe && (countmove<min)){
		mv=4;
		min=countmove;
	}
	else
		cout<<" cant down"<<endl;

	countmove=1;
	feasible=true;
	safe=false;
	while((feasible) && (!safe)){
		if((playPos.GetAbsis()-countmove>0) && (bombMap[playPos.GetOrdinat()][playPos.GetAbsis()-countmove]>countmove) && 
			(map.GetElmt(playPos.GetOrdinat(), playPos.GetAbsis()-countmove)!='#') &&  (map.GetElmt(playPos.GetOrdinat(), playPos.GetAbsis()-countmove)!='+')){
			if(bombMap[playPos.GetOrdinat()][playPos.GetAbsis()-countmove]==99){
				safe=true;
			}
			else if((map.GetElmt(playPos.GetOrdinat()-1, playPos.GetAbsis()-countmove)!='#') &&  (map.GetElmt(playPos.GetOrdinat()-1, playPos.GetAbsis()-countmove)!='+')
				&& (bombMap[playPos.GetOrdinat()-1][playPos.GetAbsis()-countmove]==99)){
				safe=true;
				countmove++;
			}
			else if((map.GetElmt(playPos.GetOrdinat()+1, playPos.GetAbsis()-countmove)!='#') &&  (map.GetElmt(playPos.GetOrdinat()+1, playPos.GetAbsis()-countmove)!='+')
				&& (bombMap[playPos.GetOrdinat()+1][playPos.GetAbsis()-countmove]==99)){
				safe=true;
				countmove++;
			}
			else
				countmove++;
		}
		else if( (bombMap[playPos.GetOrdinat()][playPos.GetAbsis()-countmove]<countmove))
			safe=true;
		else
			feasible=false;
	}
	if(safe && (countmove<min)){
		min=countmove;
		mv=2;
	}
	else
		cout<<"cant left"<<endl;

	countmove=1;
	feasible=true;
	safe=false;
	while((feasible) && (!safe)){
		if((playPos.GetOrdinat()-countmove>0) && (bombMap[playPos.GetOrdinat()-countmove][playPos.GetAbsis()]>countmove) && 
			(map.GetElmt(playPos.GetOrdinat()-countmove, playPos.GetAbsis())!='#') && (map.GetElmt(playPos.GetOrdinat()-countmove, playPos.GetAbsis())!='+')){
			if(bombMap[playPos.GetOrdinat()-countmove][playPos.GetAbsis()]==99){
				safe=true;
			}
			else if((map.GetElmt(playPos.GetOrdinat()-countmove, playPos.GetAbsis()-1)!='#') && (map.GetElmt(playPos.GetOrdinat()-countmove, playPos.GetAbsis()-1)!='+')
				&& (bombMap[playPos.GetOrdinat()-countmove][playPos.GetAbsis()-1]==99)){
				safe=true;
				countmove++;
			}
			else if((map.GetElmt(playPos.GetOrdinat()-countmove, playPos.GetAbsis()+1)!='#') && (map.GetElmt(playPos.GetOrdinat()-countmove, playPos.GetAbsis()+1)!='+')
				&& (bombMap[playPos.GetOrdinat()-countmove][playPos.GetAbsis()+1]==99)){
				safe=true;
				countmove++;
			}
			else
				countmove++;
		}
		else if( (bombMap[playPos.GetOrdinat()-countmove][playPos.GetAbsis()]<countmove))
			safe=true;
		else
			feasible=false;
	}
	if(safe && (countmove<min)){
		min=countmove;
		mv=1;
	}
	else
		cout<<"cant up"<<endl;

	if(min!=map.GetWidth()){
		move=mv;
		return true;
	}
	else{
		return false;
	}
}

bool GameState::get_power_up(Point P, int& move){
	const int rad=7;
	int start_row;
	int start_col;
	int last_row;
	int last_col;
	int mv;

	if(P.GetOrdinat()-rad>0)
		start_row=P.GetOrdinat()-rad;
	else
		start_row=1;

	if(P.GetOrdinat()+rad<map.GetHeight())
		last_row=P.GetOrdinat()+rad;
	else
		last_row=map.GetHeight()-1;

	if(P.GetAbsis()-rad>0)
		start_col=P.GetAbsis()-rad;
	else
		start_col=1;

	if(P.GetAbsis()+rad<map.GetWidth())
		last_col=P.GetAbsis()+rad;
	else
		last_col=map.GetWidth()-1;

	int min=map.GetWidth();
	int x=P.GetAbsis()-1;
	int y=P.GetOrdinat();
	bool found=false;
	bool feasible=true;
	int countmove=1;
	while((x>=start_col) && (!found) && feasible){
		if(map.GetElmt(y,x)=='!'){
			found=true;
		}
		else if((map.GetElmt(y,x)=='#') || (map.GetElmt(y,x)=='+') || (in_danger(Point(x,y))))
			feasible=false;
		else if(map.GetElmt(y-1, x)=='!'){
			countmove++;
			found=true;
		}
		else if(map.GetElmt(y+1, x)=='!'){
			countmove++;
			found=true;
		}
		else{
			countmove++;
			x--;
		}
	}
	if(found){
		if(countmove<min){
			min=countmove;
			mv=2;
			cout<<"left"<<endl;
		}
	}

	x=P.GetAbsis()+1;
	y=P.GetOrdinat();
	found=false;
	feasible=true;
	countmove=1;
	while((x<=last_col) && (!found) && feasible){
		if(map.GetElmt(y,x)=='!'){
			found=true;
		}
		else if((map.GetElmt(y,x)=='#') || (map.GetElmt(y,x)=='+') ||(in_danger(Point(x,y))))
			feasible=false;
		else if(map.GetElmt(y-1, x)=='!'){
			countmove++;
			found=true;
		}
		else if(map.GetElmt(y+1, x)=='!'){
			countmove++;
			found=true;
		}
		else{
			countmove++;
			x++;
		}
	}
	if(found){
		if(countmove<min){
			min=countmove;
			mv=3;
			cout<<"right"<<endl;
		}
	}

	x=P.GetAbsis();
	y=P.GetOrdinat()-1;
	found=false;
	feasible=true;
	countmove=1;
	while((y>start_row) && (!found) && feasible){
		if(map.GetElmt(y,x)=='!'){
			found=true;
		}
		else if((map.GetElmt(y,x)=='#') || (map.GetElmt(y,x)=='+') || (in_danger(Point(x,y))))
			feasible=false;
		else if(map.GetElmt(y, x-1)=='!'){
			countmove++;
			found=true;
		}
		else if(map.GetElmt(y, x+1)=='!'){
			countmove++;
			found=true;
		}
		else{
			countmove++;
			y--;
			cout<<"up"<<endl;
		}
	}
	if(found){
		if(countmove<min){
			min=countmove;
			mv=1;
		}
	}

	x=P.GetAbsis();
	y=P.GetOrdinat()+1;
	found=false;
	feasible=true;
	countmove=1;
	while((y<=last_row) && (!found) && feasible){
		if(map.GetElmt(y,x)=='!'){
			found=true;
		}
		else if((map.GetElmt(y,x)=='#') || (map.GetElmt(y,x)=='+') || (in_danger(Point(x,y))))
			feasible=false;
		else if(map.GetElmt(y, x-1)=='!'){
			countmove++;
			found=true;
		}
		else if(map.GetElmt(y, x+1)=='!'){
			countmove++;
			found=true;
		}
		else{
			countmove++;
			y++;
		}
	}
	if(found){
		if(countmove<min){
			min=countmove;
			mv=4;
			cout<<"down"<<endl;
		}
	}

	if(min!=map.GetWidth()){
		move=mv;
		return true;
	}
	else
		return false;
}

bool GameState::get_wall(Point P, int& move){
	const int rad=10;
	int start_row;
	int start_col;
	int last_row;
	int last_col;
	int mv;

	if(P.GetOrdinat()-rad>0)
		start_row=P.GetOrdinat()-rad;
	else
		start_row=1;

	if(P.GetOrdinat()+rad<map.GetHeight())
		last_row=P.GetOrdinat()+rad;
	else
		last_row=map.GetHeight()-1;

	if(P.GetAbsis()-rad>0)
		start_col=P.GetAbsis()-rad;
	else
		start_col=1;

	if(P.GetAbsis()+rad<map.GetWidth())
		last_col=P.GetAbsis()+rad;
	else
		last_col=map.GetWidth()-1;

	int min=map.GetWidth();
	int x=P.GetAbsis()-1;
	int y=P.GetOrdinat();
	bool found=false;
	bool feasible=true;
	int countmove=1;
	while((x>=start_col) && (!found) && feasible){
		Point p(x,y);
		if(map.GetElmt(y,x)=='+'){
			found=true;
		}
		else if((map.GetElmt(y,x)=='#') || (in_danger(p)))
			feasible=false;
		else if(map.GetElmt(y-1, x)=='+'){
			countmove++;
			found=true;
		}
		else if(map.GetElmt(y+1, x)=='+'){
			countmove++;
			found=true;
		}
		else{
			countmove++;
			x--;
		}
	}
	if(found){
		if(countmove<min){
			min=countmove;
			mv=2;
			cout<<"left"<<endl;
		}
	}

	x=P.GetAbsis()+1;
	y=P.GetOrdinat();
	found=false;
	feasible=true;
	countmove=1;
	while((x<=last_col) && (!found) && feasible){
		Point p(x,y);
		if(map.GetElmt(y,x)=='+'){
			found=true;
		}
		else if((map.GetElmt(y,x)=='#') || (in_danger(p)))
			feasible=false;
		else if(map.GetElmt(y-1, x)=='+'){
			countmove++;
			found=true;
		}
		else if(map.GetElmt(y+1, x)=='+'){
			countmove++;
			found=true;
		}
		else{
			countmove++;
			x++;
		}
	}
	if(found){
		if(countmove<min){
			min=countmove;
			mv=3;
			cout<<"right"<<endl;
		}
	}

	x=P.GetAbsis();
	y=P.GetOrdinat()-1;
	found=false;
	feasible=true;
	countmove=1;
	while((y>start_row) && (!found) && feasible){
		Point p(x,y);
		if(map.GetElmt(y,x)=='+'){
			found=true;
		}
		else if((map.GetElmt(y,x)=='#') || (in_danger(p)))
			feasible=false;
		else if(map.GetElmt(y, x-1)=='+'){
			countmove++;
			found=true;
		}
		else if(map.GetElmt(y, x+1)=='+'){
			countmove++;
			found=true;
		}
		else{
			countmove++;
			y--;
			cout<<"up"<<endl;
		}
	}
	if(found){
		if(countmove<min){
			min=countmove;
			mv=1;
		}
	}

	x=P.GetAbsis();
	y=P.GetOrdinat()+1;
	found=false;
	feasible=true;
	countmove=1;
	while((y<=last_row) && (!found) && feasible){
		Point p(x,y);
		if(map.GetElmt(y,x)=='+'){
			found=true;
		}
		else if((map.GetElmt(y,x)=='#') || (in_danger(p)))
			feasible=false;
		else if(map.GetElmt(y, x-1)=='+'){
			countmove++;
			found=true;
		}
		else if(map.GetElmt(y, x+1)=='+'){
			countmove++;
			found=true;
		}
		else{
			countmove++;
			y++;
		}
	}
	if(found){
		if(countmove<min){
			min=countmove;
			mv=4;
			cout<<"down"<<endl;
		}
	}

	if(min!=map.GetWidth()){
		move=mv;
		return true;
	}
	else
		return false;
}

int GameState::get_near_bomb(Point P)
{
	bool found=false;
	int move=0;

	for(int i=0; i<bomb.size() && (!found); i++){
		if(P.GetAbsis()==bomb[i].GetPosisi().GetAbsis()){
			if (abs(bomb[i].GetPosisi().GetAbsis() - P.GetAbsis()) <= bomb[i].GetJarak())
			{
				if(!wall_in_column(bomb[i].GetPosisi(), P)){
					if (bomb[i].GetPosisi().GetAbsis() > P.GetAbsis())
						move=3;
					else
						move=2;
				}
			}
		}
		else if(P.GetOrdinat()==bomb[i].GetPosisi().GetOrdinat()){
			if (abs(bomb[i].GetPosisi().GetOrdinat() - P.GetOrdinat()) <= bomb[i].GetJarak())
			{
				if(!wall_in_row(bomb[i].GetPosisi(), P)){
					if (bomb[i].GetPosisi().GetOrdinat() > P.GetOrdinat())
						move=1;
					else
						move=4;
				}
			}
		}
	}
	return move;
}

bool GameState::other_in_my_reach(char playerKey, Point P, int rad)
{
	bool found=false;
	for(int i=0; (i<player.size()) && (!found); i++){
		if(player[i].GetKey()!=playerKey){
			if(player[i].GetPosisi().GetAbsis()==P.GetAbsis()){
				if((abs(player[i].GetPosisi().GetOrdinat()-P.GetOrdinat())<=rad) &&(!wall_in_column(player[i].GetPosisi(), P)))
					found=true;
			}
			else if(player[i].GetPosisi().GetOrdinat()==P.GetOrdinat()){
				if((abs(player[i].GetPosisi().GetAbsis()-P.GetAbsis())<=rad)&& (!wall_in_row(player[i].GetPosisi(), P)))
					found=true;
			}
		}
	}
	return found;
}