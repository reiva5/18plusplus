#ifndef BOMB__H
#define BOMB__H
class Bomb{
	public:
		Bomb(); //Inisiasi bomb secara default
		Bomb(int drs, int rng); //Inisiasi bomb dengan durasi dan range tertentu
		void Blast(); //Jika durasi habis, bomb blast
		int GetRange(); //Mengembalikan nilai range dari bomb
		int GetDurasi(); //Mengembalikan nilai dari durasi bomb
		void SetDurasi(int n); //Memasukkan nilai durasi ke dirinya sendir
	private:
		int range;
		int durasi;
};

#endif