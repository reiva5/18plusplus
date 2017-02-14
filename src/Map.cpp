#include "Map.h"
#include <iostream>

using namespace std;
using json=nlohmann::json;

Map::Map()
{
	mapheight=21;
	mapwidth=21;

	elemen = new char*[mapheight];
	for(int i=0; i<mapwidth; i++)
	{
		elemen[i]= new char[mapwidth];
	}
}

Map::Map(json& j)
{
	mapwidth=j["MapWidth"].get<int>();
	mapheight=j["MapHeight"].get<int>();

	elemen = new char*[mapheight];
	for(int i=0; i<mapwidth; i++)
	{
		elemen[i]= new char[mapwidth];
	}

	json gameBlocks=j["GameBlocks"];
	for (auto i : gameBlocks)
	{
		for (auto k : i)
		{
			if(k["Bomb"]!=NULL)
			{
				elemen[k["Location"]["Y"].get<int>()-1][k["Location"]["X"].get<int>()-1]='0';
			}
			else if(k["Entity"]["$type"]==NULL)
			{
				if(k["PowerUp"]!=NULL)
				{
					elemen[k["Location"]["Y"].get<int>()-1][k["Location"]["X"].get<int>()-1]='!';
				}
				else
				{
					elemen[k["Location"]["Y"].get<int>()-1][k["Location"]["X"].get<int>()-1]=' ';
				}
			}
			else if(k["Entity"]["$type"]=="Domain.Entities.IndestructibleWallEntity, Domain")
			{
				elemen[k["Location"]["Y"].get<int>()-1][k["Location"]["X"].get<int>()-1]='#';
			}
			else if(k["Entity"]["$type"]=="Domain.Entities.DestructibleWallEntity, Domain")
			{	
				elemen[k["Location"]["Y"].get<int>()-1][k["Location"]["X"].get<int>()-1]='+';
			}
		}
	}
}

Map::~Map()
{
	for(int i=0; i<mapheight; i++)
	{
		delete [] elemen[i];
	}
	delete [] elemen;
}

Map& Map::operator=(const Map& m)
{
	this->mapwidth=m.mapwidth;
	this->mapheight=m.mapheight;

	for(int i=0; i<mapheight; i++)
	{
		delete [] elemen[i];
	}
	delete [] elemen;

	elemen = new char*[mapheight];
	for(int i=0; i<mapwidth; i++)
	{
		elemen[i]= new char[mapwidth];
	}

	for(int i=0; i<mapheight; i++)
	{
		for(int j=0; j<mapwidth; j++)
		{
			elemen[i][j]=m.elemen[i][j];
		}
	}

	return *this;
}

Map::Map(Map& m)
{
	this->mapwidth=m.mapwidth;
	this->mapheight=m.mapheight;

	elemen = new char*[mapheight];
	for(int i=0; i<mapwidth; i++)
	{
		elemen[i]= new char[mapwidth];
	}

	for(int i=0; i<mapheight; i++)
	{
		for(int j=0; j<mapwidth; j++)
		{
			elemen[i][j]=m.elemen[i][j];
		}
	}
}

char Map::GetElmt(int y, int x)
{
	return elemen[y][x];
}

int Map::GetWidth()
{
	return mapwidth;
}

int Map::GetHeight()
{
	return mapheight;
}

bool Map::IsBreakable(Point P)
{
	return ((GetElmt(P.GetOrdinat(), P.GetAbsis()-1)=='+')||(GetElmt(P.GetOrdinat()-1, P.GetAbsis())=='+')
			||(GetElmt(P.GetOrdinat(), P.GetAbsis()+1)=='+')||(GetElmt(P.GetOrdinat()+1, P.GetAbsis())=='+'));
}