#ifndef _SECTOR_H_
#define _SECTOR_H_

#include <SFML/Graphics.hpp>

class Sector
{
public:
	Sector(int x, int y, int radius, int piece);
	~Sector();

	sf::ConvexShape Pie, Treble, Fat, Double;

private:
	sf::ConvexShape Circular_arc(double x, double y, double endRadius, double startRadius, double startAngle, double endAngle);
	const double pi = 3.14159265358;
};

#endif