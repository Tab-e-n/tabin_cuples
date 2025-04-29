#ifndef CUPUNITS
#define CUPUNITS

#include <raylib.h>
#include "cuplib.h"

#define MAX_UNITS 32
#define CUPS_PER_UNIT 5

#define CUP_SIZE 32

typedef struct Cup
{
	int pattern, // Which eyes and potencialy patterns it has
	    animation; // What animations does it do while attacking, walking etc.
	Vector2 offset;
} Cup;

typedef struct Unit
{
	Vector2 position;
	int health,
	    type;
	char side;
	Cup cups[CUPS_PER_UNIT];
} Unit;

Rectangle UnitDetectionArea(Unit unit);
Rectangle UnitAttackArea(Unit unit);

void DrawUnitDebug(Unit unit);

#endif
