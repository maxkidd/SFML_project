#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <random>
#include <time.h>

#include "InteractiveGame.h"
#include "AIChampionship.h"

int main()
{
	srand(time(NULL));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(600, 600), "Dart Game", sf::Style::Default, settings);


	int playerScoreArray[8][8]{};

	int aiPlayTimes{ 100000 };
	for (int i{ 0 }; i < aiPlayTimes; ++i)
	{
		// Play championship
		AIChampionship aiChampionship = AIChampionship();
		aiChampionship.Play();

		// Store score in a 2d array
		playerScoreArray[aiChampionship.Player1Wins()][aiChampionship.Player2Wins()]++;
	}

	for (int i{ 0 }; i < 8; ++i)
	{
		for (int j{ 0 }; j < 8; ++j)
		{
			// Only print out numbers with 7 (because thats the end of the game)
			if (i == 7 || j == 7)
				std::cout << "Joe " << i << " - " << j << " Sid ----- Frequency: " 
				<< playerScoreArray[i][j] << " Percentage: " 
				<< (float)(100 * (float)playerScoreArray[i][j] / (float)aiPlayTimes) << "%" << std::endl;
		}
	}

	while (window.isOpen())
	{
		InteractiveGame interactiveGame = InteractiveGame(&window);
	}
	return 0;
}