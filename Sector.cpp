#include "Sector.h"
#include <Math.h>

#define PI (3.141592653589793)

Sector::Sector(int x, int y, int radius, int piece)
{

	Pie = Circular_arc(x, y, (radius / 20)*9, (radius / 20), -9 + (piece * 18), 9 + (piece * 18));
	Treble = Circular_arc(x, y, (radius / 20)*10, (radius / 20)*9, -9 + (piece * 18), 9 + (piece * 18));
	Fat = Circular_arc(x, y, (radius / 20)*19, (radius / 20)*10, -9 + (piece * 18), 9 + (piece * 18));
	Double = Circular_arc(x, y, (radius / 20)*20, (radius / 20)*19, -9 + (piece * 18), 9 + (piece * 18));

}

sf::ConvexShape Sector::Circular_arc(double x, double y, double endRadius, double startRadius, double startAngle, double endAngle)

{
	sf::ConvexShape convex;

	convex.setPointCount(40);

	// Lower left
	double currentX{ x + startRadius * sin(startAngle * PI / 180) };
	double currentY{ y - startRadius * cos(startAngle * PI / 180) };

	convex.setPoint(0, sf::Vector2f(currentX, currentY));

	// Upper left
	currentX = x + endRadius * sin(startAngle * PI / 180);
	currentY = y - endRadius * cos(startAngle * PI / 180);

	convex.setPoint(1, sf::Vector2f(currentX, currentY));

	int pointsOnArc{ 18 };
	double DegreeInRad{ 0.0174532925 };

	// Upper Accross
	for (int i{ 0 }; i < pointsOnArc; ++i)
	{
		// TODO: Sort formula out properly
		currentX = cos(DegreeInRad) * (currentX - x) - sin(DegreeInRad) * (currentY - y) + x;
		currentY = sin(DegreeInRad) * (currentX - x) + cos(DegreeInRad) * (currentY - y) + y;

		convex.setPoint(i + 2, sf::Vector2f(currentX, currentY));
	}

	// Upper right
	currentX = x + endRadius * sin(endAngle * PI / 180);
	currentY = y - endRadius * cos(endAngle * PI / 180);

	convex.setPoint(20, sf::Vector2f(currentX, currentY));

	// Lower right
	currentX = x + startRadius * sin(endAngle * PI / 180);
	currentY = y - startRadius * cos(endAngle * PI / 180);

	convex.setPoint(21, sf::Vector2f(currentX, currentY));

	// Lower across
	for (int i{ 0 }; i < pointsOnArc; ++i)
	{
		currentX = cos(-DegreeInRad) * (currentX - x) - sin(-DegreeInRad) * (currentY - y) + x;
		currentY = sin(-DegreeInRad) * (currentX - x) + cos(-DegreeInRad) * (currentY - y) + y;

		convex.setPoint(i + 22, sf::Vector2f(currentX, currentY));
	}

	return convex;

}