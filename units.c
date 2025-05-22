#include <raylib.h>
#include "cuplib.h"
#include "units.h"

Rectangle UnitDetectionArea(Unit unit)
{
	Rectangle area = (Rectangle){0};
	area.width = CUP_SIZE * (unit.area + maxf(unit.range - 1.0, 0.0));
	area.height = CUP_SIZE;
	area.x = unit.position.x;
	if(unit.side < 0)
	{
		area.x -= area.width;
	}
	area.y = unit.position.y - area.height;
	return area;
}

Rectangle UnitAttackArea(Unit unit)
{
	Rectangle area = (Rectangle){0};
	area.width = CUP_SIZE * unit.area;
	area.height = CUP_SIZE;

	float offset = unit.enemy_distance;
	if(offset > unit.range)
	{
		offset = unit.range; 
	}
	offset -= 1.0;
	if(offset < 0.0)
	{
		offset = 0.0;
	}

	area.x = unit.position.x;
	if(unit.side < 0)
	{
		area.x -= area.width * 1.5 + CUP_SIZE * offset;
	}
	else
	{
		area.x += area.width * 0.5 + CUP_SIZE * offset;
	}
	area.y = unit.position.y - area.height;
	return area;
}

Rectangle CupHitbox(Unit unit, int cup_id)
{
	Cup cup = unit.cups[cup_id];
	Vector2 offset = cup.offset;
	Rectangle hitbox;
	hitbox.x = unit.position.x - CUP_SIZE * 0.5 + offset.x;
	hitbox.y = unit.position.y - CUP_SIZE + offset.y;
	hitbox.width = CUP_SIZE;
	hitbox.height = CUP_SIZE;
	return hitbox;
}

Unit UnitInit(void)
{
	Unit unit = (Unit){0};
	unit.position = (Vector2){0, 0};
	unit.type = 0;
	unit.health = 8;
	unit.damage = 1;
	unit.incoming = 0;
	unit.state = STATE_NULL;
	unit.state_time = 1.0;
	unit.cooldown = 1.0;
	unit.speed = 16.0;
	unit.area = 1.0;
	unit.range = 1.0;
	unit.enemy_distance = 0.0;
	unit.side = 0;
	unit.alive = 1;

	for(int i = 0; i < CUPS_PER_UNIT; i++)
	{
		unit.cups[i] = (Cup){0};
	}
	unit.cups[0].active = true;

	return unit;
}

void UnitMove(Unit* unit)
{
	unit->position.x += unit->side * FRAME * unit->speed;
}

bool UnitDetectionRangeCheck(Unit* unit, Unit units[MAX_UNITS])
{
	Rectangle detect_range = UnitDetectionArea(*unit);
	for(int i = 0; i < MAX_UNITS; i++) 
	{
		Unit other = units[i];
		if(other.alive != 0) for(int j = 0; j < CUPS_PER_UNIT; j++)
		{
			if(other.cups[j].active)
			{
				Rectangle hitbox = CupHitbox(other, j);
				if(CheckCollisionRecs(detect_range, hitbox))
				{
					unit->enemy_distance = absf(unit->position.x - other.position.x) / CUP_SIZE;
					TraceLog(LOG_INFO, "Enemy dist: %f", unit->enemy_distance);
					return true;
				}
			}
		}
	}
	return false;
}

void UnitAttack(Unit* unit, Unit units[MAX_UNITS])
{
	Rectangle hurtbox = UnitAttackArea(*unit);
	for(int i = 0; i < MAX_UNITS; i++) 
	{
		Unit other = units[i];
		if(other.alive != 0) for(int j = 0; j < CUPS_PER_UNIT; j++)
		{
			if(other.cups[j].active)
			{
				Rectangle hitbox = CupHitbox(other, j);
				if(CheckCollisionRecs(hurtbox, hitbox))
				{
					units[i].incoming += unit->damage;
				}
			}
		}
	}
}

void UnitProcess(Unit* unit, Unit enemis[MAX_UNITS], Unit friends[MAX_UNITS])
{
	if(unit->alive == 0)
	{
		return;
	}
	switch(unit->state)
	{
		case STATE_MOVE:
			UnitMove(unit);
			break;
		case STATE_COOLDOWN:
			break;
		case STATE_ATTACK_START:
			break;
		case STATE_ATTACK_END:
			break;
	}
	
	unit->state_time -= FRAME;
	if(unit->state_time <= 0.0)
	{
		// STATE END
		if(unit->state == STATE_ATTACK_START)
		{
			//TraceLog(LOG_INFO, "Attack");
			UnitAttack(unit, enemis);
		}
		if(unit->state == STATE_DEATH)
		{
			unit->state = STATE_NULL;
			unit->alive = 0;
		}
		// CHANGE STATE
		switch(unit->state)
		{
			case STATE_MOVE:
				unit->state = STATE_MOVE;
				break;
			case STATE_COOLDOWN:
				unit->state = STATE_MOVE;
				break;
			case STATE_ATTACK_START:
				unit->state = STATE_ATTACK_END;
				break;
			case STATE_ATTACK_END:
				unit->state = STATE_COOLDOWN;
				break;
		}
		// STATE START
		if(unit->state == STATE_MOVE)
		{
			if(UnitDetectionRangeCheck(unit, enemis))
			{
				unit->state = STATE_ATTACK_START;
			}
		}
		switch(unit->state)
		{
			case STATE_NULL:
				unit->state_time = 1.0;
				break;
			case STATE_MOVE:
				unit->state_time = 0.1;
				break;
			case STATE_COOLDOWN:
				unit->state_time = unit->cooldown;
				break;
			case STATE_ATTACK_START:
				unit->state_time = 0.25;
				break;
			case STATE_ATTACK_END:
				unit->state_time = 0.25;
				break;
		}
	}
}

void UnitDamage(Unit* unit)
{
	if(unit->alive == 0 || unit->health <= 0)
	{
		unit->incoming = 0;
		return;
	}
	unit->health -= unit->incoming;
	unit->incoming = 0;
	if(unit->health <= 0)
	{
		unit->state = STATE_DEATH;
		unit->state_time = 1.0;
	}
	//TraceLog(LOG_INFO, "%i", unit->health);
}

void DrawUnitDebug(Unit unit)
{
	if(unit.alive == 0)
	{
		return;
	}
	if(unit.state == STATE_MOVE)
	{
		DrawRectangleRec(UnitDetectionArea(unit), TRANS_PURPLE);
	}
	for(int i = 0; i < CUPS_PER_UNIT; i++)
	{
		DrawRectangleRec(CupHitbox(unit, i), BLACK);
	}
	if(unit.state == STATE_ATTACK_START)
	{
		DrawRectangleRec(UnitAttackArea(unit), TRANS_RED);
	}
}
