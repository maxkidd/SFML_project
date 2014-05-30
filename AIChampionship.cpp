#include "AIChampionship.h"
#include "AIDartsGame.h"

AIChampionship::AIChampionship()
{

}

void AIChampionship::Play()
{
	while (!gameOver)
	{
		// Creates new game
		AIDartsGame currentGame = AIDartsGame();

		// Returns true if player1 wins
		bool didPlayer1Win = currentGame.PlayGame();

		// Increase game win
		if (didPlayer1Win)
			++player1;
		else
			++player2;

		// If player won championship return
		if (player1 == 7 || player2 == 7)
			return;
	}
}

int AIChampionship::Player1Wins()
{
	return player1;
}

int AIChampionship::Player2Wins()
{
	return player2;
}