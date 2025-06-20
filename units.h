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
	STATE_HEAL_COOLDOWN,
	STATE_HEAL_START,
	STATE_HEAL_END,
	STATE_STUN,
} UnitState;

typedef enum UnitType
{
	UNIT_BASE,
	UNIT_BASIC,
	UNIT_TALL,
	UNIT_THROWER,
	UNIT_PILLAR,
	UNIT_HORSE,
	UNIT_CANNON,
	UNIT_VETERAN,
	UNIT_PIRATE,
	UNIT_CLERIC,
} UnitType;

typedef enum DetectionRangeCheckType
{
	CHECK_CLOSEST,
	CHECK_FURTHEST,
} DetectionRangeCheckType;

typedef enum IdleState
{
	IDLE_STOP,
	IDLE_STAND,
	IDLE_BACKUP,
} IdleState;

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
	    heal, 
	    incoming; // * Damage is dealt after every unit is processed, stored here
	UnitState state;
	float cooldown, // Base cooldown after attacking
	      speed, // Pixels per frame
	      move_full,
	      move_wait,
	      area, // The size of the damage area in cups
	      range, // How many cups far can the unit attack
	      length, // How many cups long is the unit
	      state_time, // * Amount of time until the state ends
	      move_time,
	      enemy_distance, // * How far the last detected enemy is, limited by range
	      knockback,
	      knockback_given,
	      stun;
	char direction, // 1 (player) or -1 (opponent)
	     alive, // * Is unit alive and should it be processed
	     idle_state, // * When overlaping another unit, backup and stuff.
	     move_chain,
	     move_chain_goal;
	Vector2 health_bar_offset;
	Cup cups[CUPS_PER_UNIT];
} Unit;

typedef struct Side
{
	Vector2 spawn_position;
	char direction,
	     current_unit;
	Unit units[MAX_UNITS];
} Side;

Rectangle UnitDetectionArea(Unit unit);
Rectangle UnitFrontArea(Unit unit);
Rectangle UnitAttackArea(Unit unit);
Rectangle CupHitbox(Unit unit, int cup_id);
Vector2 CupPosition(Unit unit, int cup_id);

Unit UnitInit(void);
Unit MakeUnit(UnitType type, Vector2 position, char direction);

void UnitMove(Unit* unit, float mult);
bool UnitDetectionRangeCheck(Unit* unit, Side* side, DetectionRangeCheckType type);
bool UnitCanPass(Unit* unit, Unit* other);
bool CupOverlapsUnit(Unit* unit, Rectangle hitbox);
char UnitFrontCheck(Unit* unit, Side* side);
void UnitAttack(Unit* unit, Side* side);
void UnitHeal(Unit* unit, Side* side);

void UnitProcess(Unit* unit, Side* enemy_side, Side* friend_side);
void UnitDamage(Unit* unit);

Side SideInit(Vector2 start_pos, char direction);
bool SpawnUnit(UnitType type, Side* side, float offset);
char BaseAlive(Side* side);

void DrawUnitDebug(Unit unit);
void DrawUnitDebugAttack(Unit unit);
void DrawHealthBar(Unit unit);

#endif
