#include "InteractiveGame.h"
#include <iostream>

InteractiveGame::InteractiveGame(sf::RenderWindow* window)
{
	dartboard1 = new DartBoard(300, 300, 200);
	player1 = Player();
	player2 = Player();
	currentPlayer = &player1;
	this->window = window;
	dartboard1->ProvideWindow(window);

	// Start game  text
	std::cout << std::endl << "New player vs player game" << std::endl;
	std::cout << "Player 1's points: " << player1.GetPoints() << std::endl;
	std::cout << "Player 2's points: " << player2.GetPoints() << std::endl << std::endl;
	std::cout << "Player " << player + 1 << "'s turn" << std::endl;

	while (window->isOpen())
	{
		Update();
		if (gameOver)
			return;
	}
}

void InteractiveGame::Update()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left) // If event is left mouse button
			{
				if (dartboard1->GetSegment() != Null) // If aiming at a board piece
				{
					// Throw at the board
					currentPlayer->ThrowAtBoard(dartboard1->GetSectorPoints(), dartboard1->GetSegment());
					std::cout << "Current points for player " << player + 1 << ": " << currentPlayer->GetPoints() << std::endl;
					currentThrow++;

					// If player won
					if (currentPlayer->GetPoints() == 0)
					{
						// Won
						std::cout << "Player " << player + 1 << " has won!" << std::endl;
						gameOver = true;
						return;
					}

					// If score is an impossible score
					if (currentPlayer->GetPoints() <= 1)
					{
						currentPlayer->SetPoints(startOfThrowsScore);
						std::cout << "Illegal amount of points" << std::endl;;
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
						startOfThrowsScore = player1.GetPoints();
						std::cout << std::endl << "Player " << player + 1 << "'s turn" << std::endl;

					}
				}
			}
			break;
		}
	}

	// Clear window
	window->clear();

	dartboard1->UpdateDisplay();



	// Display window
	window->display();
}