#include "AIDartsGame.h"
#include <iostream>

AIDartsGame::AIDartsGame()
{
	// Setup players
	player1 = Player();
	player2 = Player();
	player1.SetAccuracy(70);
	player2.SetAccuracy(72);
}

bool AIDartsGame::PlayGame()
{
	// Random player goes first
	if (rand() % 2 == 0)
		currentPlayer = &player1;
	else
		currentPlayer = &player2;

	while (!gameOver)
	{
		Update();
	}

	// Return after game over with which player won
	if (currentPlayer == &player1)
		return true;
	else
		return false;
}

void AIDartsGame::Update()
{
	currentThrow++;

	if (currentPlayer->GetPoints() <= 40) // If player can win on a double
	{
		if ((currentPlayer->GetPoints() % 2) == 0) // Make sure it's even (so can get double)
		{
			currentPlayer->ThrowAtBoard(currentPlayer->GetPoints() / 2, Double); // Aim at a winner
		}
		else
		{
			currentPlayer->ThrowAtBoard(1, Single); // Else aim for 1
		}
	}
	else if (currentPlayer->GetPoints() == 50)
	{
		currentPlayer->ThrowAtBoard(0, Bull);
	}
	else if (currentPlayer->GetPoints() <= 40 + 20) // Else if can get into a winning position with a single
	{
		currentPlayer->ThrowAtBoard(currentPlayer->GetPoints() - 40, Single);
	}
	else if (currentPlayer->GetPoints() <= 40 + 40) // Else if can get into a winning position with a double
	{
		if ((currentPlayer->GetPoints() % 2) == 0) // Make sure it's even else it has to be a triple to get into winning position
		{
			currentPlayer->ThrowAtBoard((currentPlayer->GetPoints() - 40) / 2, Double);
		}
		else
		{
			currentPlayer->ThrowAtBoard((currentPlayer->GetPoints() - 40) / 3, Triple);
		}
	}
	else // Has to be a triple
	{
		currentPlayer->ThrowAtBoard(20, Triple);
	}


	// If player won
	if (currentPlayer->GetPoints() == 0)
	{
		// Game over and return to constructor
		gameOver = true;
		return;
	}

	// If score is an impossible score
	if (currentPlayer->GetPoints() <= 1)
	{
		currentPlayer->SetPoints(startOfThrowsScore);
		currentThrow = 3;
	}

	// Switch player
	if (currentThrow == 3)
	{
		player = !player;
		if (currentPlayer == &player1)
			currentPlayer = &player2;
		else
			currentPlayer = &player1;
		currentThrow = 0;
		startOfThrowsScore = currentPlayer->GetPoints();

	}
}