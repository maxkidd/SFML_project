#ifndef _DARTBOARD_H_
#define _DARTBOARD_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include "Sector.h"
#include "Types.h"

class DartBoard
{
public:
	DartBoard(double x, double y, double radius);

	void UpdateDisplay();
	void ProvideWindow(sf::RenderWindow *window);
	std::vector<sf::ConvexShape*> convexShapes;
	int GetSectorPoints();
	BoardSegment GetSegment();

private:
	bool PointIntersectingShape(int numVert, sf::Shape* shape, float pointX, float pointY);

	const static int pointsPerSector[];
	std::vector<Sector*> sectors;
	std::vector<sf::Text> borderText;
	sf::CircleShape innerBull, outerBull;
	sf::RenderWindow* window;

	BoardSegment currentSegment;
	int currentSector;

	sf::Font font;
	const static int numOfSectors;
};

#endif