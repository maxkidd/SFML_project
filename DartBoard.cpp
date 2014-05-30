#include "DartBoard.h"
#include <iostream>

const int DartBoard::pointsPerSector[20] = { 20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5 };
const int DartBoard::numOfSectors = 20;

#define PI (3.141592653589793)

DartBoard::DartBoard(double x, double y, double radius)
{
	// Load font
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Error loading font" << std::endl;

	for (int i{ 0 }; i < numOfSectors; ++i)
	{
		// Sections
		sectors.push_back(new Sector(x, y, radius, i));

		convexShapes.push_back(&sectors[i]->Pie);
		convexShapes.push_back(&sectors[i]->Treble);
		convexShapes.push_back(&sectors[i]->Fat);
		convexShapes.push_back(&sectors[i]->Double);

		// Text
		sf::Text text = sf::Text();
		text.setFont(font);
		text.setString(std::to_string(pointsPerSector[i]));
		text.move(-12, -12); // Move to center text
		text.move(x + (radius / 20) * 22 * sin((i * 18) * PI / 180), y - (radius / 20) * 22 * cos((i * 18) * PI / 180)); // Move to edges of board
		text.setCharacterSize(24);
		text.setColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);

		borderText.push_back(text);

	}

	// Bullseye
	innerBull = sf::CircleShape(radius / 40);
	innerBull.setPosition(x - radius / 40, y - radius / 40);
	outerBull = sf::CircleShape(radius / 20);
	outerBull.setPosition(x - radius / 20, y - radius / 20);
}

BoardSegment DartBoard::GetSegment()
{
	return currentSegment;
}
int DartBoard::GetSectorPoints()
{
	return pointsPerSector[currentSector];
}

void DartBoard::ProvideWindow(sf::RenderWindow *window)
{
	this->window = window;
}

bool DartBoard::PointIntersectingShape(int numVert, sf::Shape* shape, float pointX, float pointY)
{
	bool isIntersecting{ false };
	for (int i{ 0 }, j{ numVert - 1 }; i < numVert; j = i++)
	{
		if ((((shape->getPoint(i).y  + shape->getPosition().y)>pointY) != ((shape->getPoint(j).y  + shape->getPosition().y)>pointY))
			&& (pointX < ((shape->getPoint(j).x  + shape->getPosition().x) - (shape->getPoint(i).x  + shape->getPosition().x)) * (pointY - (shape->getPoint(i).y  + shape->getPosition().y)) / ((shape->getPoint(j).y  + shape->getPosition().y) - (shape->getPoint(i).y  + shape->getPosition().y)) + (shape->getPoint(i).x  + shape->getPosition().x)))
			isIntersecting = !isIntersecting;
	}
	return isIntersecting;
}


void DartBoard::UpdateDisplay()
{

	currentSegment = Null;

	// Check mouse collision with polygons
	for (int i = 0; i < convexShapes.size(); ++i)
	{
		if (PointIntersectingShape(convexShapes[i]->getPointCount(), convexShapes[i], sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			convexShapes[i]->setFillColor(sf::Color::Yellow);
			currentSector = i/4;

			switch (i % 4)
			{
			case 0:
			case 2:
				currentSegment = Single;
				break;
			case 1:
				currentSegment = Triple;
				break;
			case 3:
				currentSegment = Double;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (i % 8)
			{
			case 0:
			case 2:
				convexShapes[i]->setFillColor(sf::Color::Black);
				break;
			case 1:
			case 3:
				convexShapes[i]->setFillColor(sf::Color::Red);
				break;
			case 4:
			case 6:
				convexShapes[i]->setFillColor(sf::Color::White);
				break;
			case 5:
			case 7:
				convexShapes[i]->setFillColor(sf::Color::Green);
				break;
			}

		}
	}

	if (PointIntersectingShape(innerBull.getPointCount(), &innerBull, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)
		|| PointIntersectingShape(outerBull.getPointCount(), &outerBull, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
	{
		innerBull.setFillColor(sf::Color::Yellow);
		outerBull.setFillColor(sf::Color::Yellow);
		currentSegment = Bull;
	}
	else
	{
		innerBull.setFillColor(sf::Color::Red);
		outerBull.setFillColor(sf::Color::Green);
	}
	// Display shapes
	for (size_t i{ 0 }; i < convexShapes.size(); ++i)
	{
		window->draw(*convexShapes[i]);
	}
	for (size_t i{ 0 }; i < borderText.size(); ++i)
	{
		window->draw(borderText[i]);
	}


	window->draw(outerBull);
	window->draw(innerBull);
}