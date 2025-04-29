#ifndef CUPUNITS
#define CUPUNITS

#include <raylib.h>
#include "cuplib.h"

#define MAX_UNITS 32
#define CUPS_PER_UNIT 5

#define CUP_SIZE 32

typedef enum UnitState
{
	STATE_NULL,
	STATE_MOVE,
	STATE_COOLDOWN,
	STATE_ATTACK_START,
	STATE_ATTACK_END,
} UnitState;

typedef struct Cup
{
	bool active;
	int pattern,
	    animation;
	Vector2 offset;
} Cup;

typedef struct Unit
{
	Vector2 position;
	int type;
	UnitState state;
	float state_time,
	      health,
	      damage,
	      cooldown,
	      speed;
	char side;
	Cup cups[CUPS_PER_UNIT];
} Unit;

Rectangle UnitDetectionArea(Unit unit);
Rectangle UnitAttackArea(Unit unit);

Unit UnitInit(void);
void UnitMove(Unit* unit);
void UnitProcess(Unit* unit);

void DrawUnitDebug(Unit unit);

#endif
