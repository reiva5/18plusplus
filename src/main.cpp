#include <iostream>
#include <fstream>
#include "GameState.h"

#include <stdlib.h>
#include <time.h>

using namespace std;
using json=nlohmann::json;

void writeMoveFile(string filePath, int i)
{
	cout << "Writing move file " << filePath + "/" + "move.txt" << std::endl;
	ofstream outfile(filePath + "/" + "move.txt");

	if (outfile.is_open())
	{
		outfile << i << std::endl;
		outfile.close();
	}
}

int move(Point& P, Map& M, GameState& state){
	srand(time(NULL));

	int i=rand()%4+1;
	bool found=false;

	Point up(P.GetAbsis(), P.GetOrdinat()-1);
	Point down(P.GetAbsis(), P.GetOrdinat()+1);
	Point right(P.GetAbsis()+1, P.GetOrdinat());
	Point left(P.GetAbsis()-1, P.GetOrdinat());
	while(!found){
		if(i==2){
			if((P.GetAbsis()-1>=0) && (M.GetElmt(P.GetOrdinat(), P.GetAbsis()-1)!='#') && ((M.GetElmt(P.GetOrdinat(), P.GetAbsis()-1)!='+'))&& (!state.in_danger(left))){
				found=true;
				return i;
			}
			else{
				i++;
				cout<<"not left"<<endl;
			}
		}
		else if(i==1){
			if((P.GetOrdinat()-1>=0) && (M.GetElmt(P.GetOrdinat()-1, P.GetAbsis())!='#') && (M.GetElmt(P.GetOrdinat()-1, P.GetAbsis())!='+')&& (!state.in_danger(up))){
				found=true;
				return i;
			}
			else{ 
				i++;
				cout<<"not up"<<endl;
			}
		}
		else if(i==3){
			if((P.GetAbsis()+1<M.GetWidth()) && (M.GetElmt(P.GetOrdinat(), P.GetAbsis()+1)!='#') && (M.GetElmt(P.GetOrdinat(), P.GetAbsis()+1)!='#')&& (!state.in_danger(right))){
				found=true;
				return i;
			}
			else{
				i++;
				cout<<"not right"<<endl;
			}
		}
		else if(i==4){
			if((P.GetOrdinat()+1<M.GetHeight())&& (M.GetElmt(P.GetOrdinat()+1, P.GetAbsis())!='#') && (M.GetElmt(P.GetOrdinat()+1, P.GetAbsis())!='+')&& (!state.in_danger(down))){
				found=true;
				return i;
			}
			else{
				i=1;
				cout<<"not down"<<endl;
			}
		}
	}
}

int main(int argc, char** argv){
	string filePath = argv[2];

	cout << "Args: " << argc << std::endl;
	cout << "Player Key: " << argv[1] << std::endl;
	cout << "File Path: " << argv[2] << std::endl;

	string mapPath=filePath;
	mapPath=mapPath.substr(0, mapPath.size()-2)+"/state.json";

	ifstream json_file;
	json_file.open(mapPath);
	json j;
	json_file>>j;
	json_file.close();
	
	GameState state(j);
	Map m= state.GetMap();

	char playerKey=argv[1][0];
	vector<Player> p=state.GetPlayer();
	bool found=false;
	Point playerPosisi;
	int i=0;
	int myBombBag;
	while(!found){
		if(p[i].GetKey()==playerKey){
			playerPosisi=p[i].GetPosisi();
			myBombBag=p[i].GetBombBag();
			found=true;
		}
		else
			i++;
	}

	int nextmove;
	if(state.in_danger(playerPosisi)){
		if(state.move_away(playerPosisi, nextmove))
			cout<<"moveaway"<<endl;
		else
			nextmove=move(playerPosisi, m, state);
	}
	else{
		if(state.get_power_up(playerPosisi, nextmove))
			cout<<"getting power up"<<endl;
		else if(((m.GetElmt(playerPosisi.GetOrdinat(), playerPosisi.GetAbsis()-1)=='+')||(m.GetElmt(playerPosisi.GetOrdinat()-1, playerPosisi.GetAbsis())=='+')
			||(m.GetElmt(playerPosisi.GetOrdinat(), playerPosisi.GetAbsis()+1)=='+')||(m.GetElmt(playerPosisi.GetOrdinat()+1, playerPosisi.GetAbsis())=='+'))
			&&(myBombBag>0)){
			nextmove=5;
			cout<<"drop bomb"<<endl;
		}
		else if(state.get_wall(playerPosisi, nextmove))
			cout<<"getting wall"<<endl;
		else{
			nextmove=move(playerPosisi, m, state);	
			cout<<"free move"<<endl;
		}

	}
	
	writeMoveFile(filePath, nextmove);

	return 0;
}