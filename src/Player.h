#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	public:
		Player();
		
		Player(Bomb B);

		Player(Posisi Y);

		Player(Bomb B, Posisi Y);

		Player(const Player& P);

		~Player();

		Player& operator= (Player& P);

		
	private:
		Bomb B;
		Posisi P;
};

#endif