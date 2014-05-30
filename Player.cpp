#include "Player.h"

void Player::SetAccuracy(int acc)
{
	accuracy = acc;
}

int Player::throw_bull(int p) {

	//  Throw for the bull with accuracy p%  (20<p<85)

	int r = rand() % 100;

	if (r<(p - 20))
		return 50;
	else if (r<85)
		return 25;
	else
		return 1 + rand() % 20;
}


int Player::throw_treble(int d, int p) {

	//  return result of throwing for treble d with accuracy p%  (o<90)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { { 0, 20, 15, 17, 18, 12, 13, 19, 16, 14, 6, 8, 9, 4, 11, 10, 7, 2, 1, 3, 5 },
	{ 0, 18, 17, 19, 13, 20, 10, 16, 11, 12, 15, 14, 5, 6, 9, 2, 8, 3, 4, 7, 1 } };

	int r = rand() % 100;

	if (r<p)
		return 3 * d;
	else if (r<90)
		return d;
	else if (r<93)
		return 3 * bd[0][d];
	else if (r<96)
		return 3 * bd[1][d];
	else if (r<98)
		return bd[0][d];
	else
		return bd[1][d];
}


int Player::throw_double(int d) {

	//  return result of throwing for double d with accuracy 80%

	// Board neighbours ignoring slot zero
	int bd[2][21] = { { 0, 20, 15, 17, 18, 12, 13, 19, 16, 14, 6, 8, 9, 4, 11, 10, 7, 2, 1, 3, 5 },
	{ 0, 18, 17, 19, 13, 20, 10, 16, 11, 12, 15, 14, 5, 6, 9, 2, 8, 3, 4, 7, 1 } };
	int r = rand() % 100;

	if (r<80)
		return 2 * d;
	else if (r<85)
		return 0;
	else if (r<90)
		return d;
	else if (r<93)
		return 2 * bd[0][d];
	else if (r<96)
		return 2 * bd[1][d];
	else if (r<98)
		return bd[0][d];
	else
		return bd[1][d];
}



int Player::throw_single(int d) {

	//  return result of throwing for single d with accuracy 88% (or 80% for the outer)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { { 0, 20, 15, 17, 18, 12, 13, 19, 16, 14, 6, 8, 9, 4, 11, 10, 7, 2, 1, 3, 5 },
	{ 0, 18, 17, 19, 13, 20, 10, 16, 11, 12, 15, 14, 5, 6, 9, 2, 8, 3, 4, 7, 1 } };
	int r = rand() % 100;

	if (d == 25){		// outer  80%
		if (r<80)
			return 25;
		else if (r<90)
			return 50;
		else
			return 1 + rand() % 20;
	}
	else			// 1 to 20 single
	if (r<88)
		return d;
	else if (r<92)
		return bd[0][d];
	else if (r<96)
		return bd[1][d];
	else if (r<98)
		return 3 * d;
	else
		return 2 * d;
}

void Player::ThrowAtBoard(int sectionPoints, BoardSegment segment)
{
	switch (segment)
	{
	case Single:
		currentPoints -= throw_single(sectionPoints);
		break;
	case Double:
		currentPoints -= throw_double(sectionPoints);
		break;
	case Triple:
		currentPoints -= throw_treble(sectionPoints, accuracy);
		break;
	case Bull:
		currentPoints -= throw_bull(accuracy);
		break;
	case Null:
		break;
	}
	// Make move illegal if ending on a single
	if (currentPoints == 0 && (segment == Single || segment == Triple))
		currentPoints = -1;
}
