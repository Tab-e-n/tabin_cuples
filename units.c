#include <raylib.h>
#include "cuplib.h"
#include "units.h"

Rectangle UnitDetectionArea(Unit unit)
{
	Rectangle area = (Rectangle){0};
	area.width = CUP_SIZE;
	area.height = CUP_SIZE * 5;
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
	area.width = CUP_SIZE;
	area.height = CUP_SIZE;
	area.x = unit.position.x;
	if(unit.side < 0)
	{
		area.x -= area.width * 1.5;
	}
	else
	{
		area.x += area.width * 0.5;
	}
	area.y = unit.position.y - area.height;
	return area;
}

Unit UnitInit(void)
{
	Unit unit = (Unit){0};
	unit.position = (Vector2){0, 0};
	unit.type = 0;
	unit.state = STATE_NULL;
	unit.state_time = 1.0;
	unit.health = 8.0;
	unit.damage = 1.0;
	unit.cooldown = 1.0;
	unit.speed = 8.0;
	unit.side = 0;

	return unit;
}

void UnitMove(Unit* unit)
{
	unit->position.x += unit->side * FRAME * unit->speed;
}

void UnitProcess(Unit* unit)
{
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
		if(unit->state == STATE_MOVE)
		{
			// TODO: Check for cups in detection range, attack if there are.
		}
		if(unit->state == STATE_ATTACK_END)
		{
			// TODO: Check for cups in attack area, damage all cups.
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

void DrawUnitDebug(Unit unit)
{
	if(unit.state == STATE_MOVE)
	{
		DrawRectangleRec(UnitDetectionArea(unit), PURPLE);
	}
	DrawRectangle(unit.position.x - CUP_SIZE * 0.5, unit.position.y - CUP_SIZE, CUP_SIZE, CUP_SIZE, BLACK);
	if(unit.state == STATE_ATTACK)
	{
		DrawRectangleRec(UnitAttackArea(unit), RED);
	}
}
