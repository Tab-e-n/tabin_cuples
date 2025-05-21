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
	STATE_DEATH,
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
	int type,
	    health,
	    damage,
	    incoming;
	UnitState state;
	float state_time,
	      cooldown,
	      speed,
	      area,
	      range,
	      enemy_distance;
	char side,
	     alive;
	Cup cups[CUPS_PER_UNIT];
} Unit;

Rectangle UnitDetectionArea(Unit unit);
Rectangle UnitAttackArea(Unit unit);
Rectangle CupHitbox(Unit unit, int cup_id);

Unit UnitInit(void);

void UnitMove(Unit* unit);
bool UnitDetectionRangeCheck(Unit* unit, Unit units[MAX_UNITS]);
void UnitAttack(Unit* unit, Unit units[MAX_UNITS]);
void UnitProcess(Unit* unit, Unit enemis[MAX_UNITS], Unit friends[MAX_UNITS]);
void UnitDamage(Unit* unit);

void DrawUnitDebug(Unit unit);

#endif
