#ifndef CUPUNITS
#define CUPUNITS

#include <raylib.h>
#include <raymath.h>
#include "cuplib.h"

#define MAX_UNITS 32
#define CUPS_PER_UNIT 5

#define CUP_SIZE 32
#define CUP_SIZE_INV 0.03125

typedef enum UnitState
{
	STATE_NULL,
	STATE_MOVE,
	STATE_COOLDOWN,
	STATE_ATTACK_START,
	STATE_ATTACK_END,
	STATE_DEATH,
	STATE_IDLE,
} UnitState;

typedef enum UnitType
{
	UNIT_BASE,
	UNIT_BASIC,
	UNIT_TALL,
	UNIT_THROWER,
	UNIT_HORSE,
} UnitType;

typedef struct Cup
{
	bool active;
	int pattern, // What does the cup look like
	    animation; // What animations should the cup do
	Vector2 offset; // Values always positive
} Cup;

typedef struct Unit
{
	Vector2 position;
	int health, // Current health, basic unit has 8 health
	    max_health, // Max health, stays the same
	    damage, // Amount of damage dealt when unit attacks
	    incoming; // * Damage is dealt after every unit is processed, stored here
	UnitState state;
	float cooldown, // Base cooldown after attacking
	      speed, // Pixels per frame
	      area, // The size of the damage area in cups
	      range, // How many cups far can the unit attack
	      length, // How many cups long is the unit
	      state_time, // * Amount of time until the state ends
	      enemy_distance; // * How far the last detected enemy is, limited by range
	char side, // 1 (player) or -1 (opponent)
	     alive, // * Is unit alive and should it be processed
	     idle_backup; // * When overlaping another unit, backup after standing for too long.
	Vector2 health_bar_offset;
	Cup cups[CUPS_PER_UNIT];
} Unit;

Rectangle UnitDetectionArea(Unit unit);
Rectangle UnitFrontArea(Unit unit);
Rectangle UnitAttackArea(Unit unit);
Rectangle CupHitbox(Unit unit, int cup_id);

Unit UnitInit(void);
Unit MakeUnit(int type, Vector2 position, char side);

void UnitMove(Unit* unit, float mult);
bool UnitDetectionRangeCheck(Unit* unit, Unit units[MAX_UNITS]);
bool UnitCanPass(Unit* unit, Unit* other);
bool UnitFrontCheck(Unit* unit, Unit units[MAX_UNITS]);
void UnitAttack(Unit* unit, Unit units[MAX_UNITS]);

void UnitProcess(Unit* unit, Unit enemis[MAX_UNITS], Unit friends[MAX_UNITS]);
void UnitDamage(Unit* unit);

void DrawUnitDebug(Unit unit);
void DrawHealthBar(Unit unit);

#endif
