#ifndef _INTERACTIVEGAME_H_
#define _INTERACTIVEGAME_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include "DartBoard.h"
#include "Player.h"

class InteractiveGame
{
public:
	InteractiveGame(sf::RenderWindow* window);

private:
	void Update();

	sf::RenderWindow *window;
	DartBoard *dartboard1;
	Player player1, player2;
	Player *currentPlayer;
	int currentThrow{ 0 };
	int startOfThrowsScore{ 501 };
	bool player{ 0 };
	bool gameOver{ false };

};

#endif