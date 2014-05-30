#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Types.h"
#include <random>
#include <time.h>

class Player
{
public:
	Player()
	{
		currentPoints = 501;
		accuracy = 70;
	}

	int GetPoints(){ return currentPoints; }
	void SetPoints(int points){ currentPoints = points; };
	void ThrowAtBoard(int sectionPoints, BoardSegment segment);

	void SetAccuracy(int acc);
protected:
	int throw_bull(int p);
	int throw_treble(int d, int p);
	int throw_double(int d);
	int throw_single(int d);
	
	int currentPoints;
	int accuracy;
};

#endif