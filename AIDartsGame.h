#ifndef _AIDARTSGAME_H_
#define _AIDARTSGAME_H_

#include <vector>
#include "Player.h"

class AIDartsGame
{
public:
	AIDartsGame();

	// Returns true if player1 wins
	bool PlayGame();
private:
	void Update();

	Player player1, player2;
	Player *currentPlayer;
	int currentThrow{ 0 };
	int startOfThrowsScore{ 501 };
	bool player{ 0 };
	bool gameOver{ false };

};

#endif