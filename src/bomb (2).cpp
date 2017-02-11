#include "bomb.h"
//#include "player.h"

	Bomb::Bomb(){
		range=1;
		durasi=3;
	} //Inisiasi terciptanya bomb
	Bomb::Bomb(int drs, int rng){
		range=rng;
		durasi=drs;
	}//Inisiasi bomb dengan durasi dan range tertentu
	void Bomb::Blast(){
		for(int i=0; i<range; i++){

		}
	} //Jika durasi habis, bomb blast
	int Bomb::GetRange(){
		return range;
	} //Mengembalikan nilai range dari bomb
	int Bomb::GetDurasi(){
		return durasi;
	} //Mengembalikan nilai dari durasi bomb
	void Bomb::SetDurasi(int n){
		durasi=n;
	}//Memasukkan nilai durasi ke dirinya sendir
	/*private:
		int range;
		int durasi;*/