#include <raylib.h>
#include <raymath.h>
#include "cuplib.h"
#include "units.h"

Rectangle UnitDetectionArea(Unit unit)
{
	Rectangle area = (Rectangle){0};
	area.width = CUP_SIZE * maxf(unit.range - 0.75, 0.25); // + (unit.state == STATE_IDLE ? unit.area - 0.25 : 0.0));
	area.height = CUP_SIZE;
	area.x = unit.position.x;
	if(unit.direction < 0)
	{
		area.x -= area.width + CUP_SIZE * (unit.length - 0.5);
	}
	else
	{
		area.x += CUP_SIZE * (unit.length - 0.5);
	}
	area.y = unit.position.y - area.height;
	return area;
}

Rectangle UnitFrontArea(Unit unit)
{
	Rectangle area = (Rectangle){0};
	area.width = CUP_SIZE * 0.125;
	area.height = CUP_SIZE * .45;
	area.x = unit.position.x;
	if(unit.direction < 0)
	{
		area.x -= area.width + CUP_SIZE * (unit.length - 0.49);
	}
	else
	{
		area.x += CUP_SIZE * (unit.length - 0.49);
	}
	area.y = unit.position.y - area.height;
	return area;
}

Rectangle UnitAttackArea(Unit unit)
{
	Rectangle area = (Rectangle){0};
	area.width = CUP_SIZE * unit.area;
	area.height = CUP_SIZE - 1;

	area.x = unit.position.x;
	if(unit.direction < 0)
	{
		area.x -= area.width * 1.0 + CUP_SIZE * ((unit.length - 0.5) + unit.enemy_distance);
	}
	else
	{
		area.x += CUP_SIZE * ((unit.length - 0.5) + unit.enemy_distance);
	}
	area.y = unit.position.y - area.height;
	return area;
}

Rectangle CupHitbox(Unit unit, int cup_id)
{
	Cup cup = unit.cups[cup_id];
	Vector2 offset = cup.offset;
	offset.x = offset.x * (float)unit.direction;
	Rectangle hitbox;
	hitbox.x = unit.position.x - CUP_SIZE * 0.45 + offset.x;
	hitbox.y = unit.position.y - CUP_SIZE - offset.y;
	hitbox.width = CUP_SIZE * 0.9;
	hitbox.height = CUP_SIZE;
	return hitbox;
}

Vector2 CupPosition(Unit unit, int cup_id)
{
	Cup cup = unit.cups[cup_id];
	Vector2 offset = cup.offset;
	offset.x = offset.x * (float)unit.direction;
	return Vector2Add(unit.position, offset);
}

Unit UnitInit(void)
{
	Unit unit = (Unit){0};
	unit.position = (Vector2){0, 0};
	unit.health = 8;
	unit.max_health = 8;
	unit.damage = 2;
	unit.heal = 0;
	unit.incoming = 0;
	unit.state = STATE_NULL;
	unit.cooldown = 1.0;
	unit.speed = 16.0;
	unit.move_full = 1.0;
	unit.move_wait = 0.25;
	unit.area = 1.0;
	unit.range = 1.0;
	unit.length = 1.0;
	unit.state_time = 1.0;
	unit.move_time = 0.0;
	unit.enemy_distance = 0.0;
	unit.direction = 0;
	unit.alive = 1;
	unit.idle_state = IDLE_STOP;
	unit.health_bar_offset = (Vector2){0, 32};

	for(int i = 0; i < CUPS_PER_UNIT; i++)
	{
		unit.cups[i] = (Cup){0};
	}
	unit.cups[0].active = true;

	return unit;
}

Unit MakeUnit(int type, Vector2 position, char direction)
{
	Unit unit = UnitInit();
	unit.position = position;
	unit.state = STATE_IDLE;
	unit.direction = direction;

	switch(type)
	{
		case(UNIT_BASE):
			unit.max_health = 80;
			unit.damage = 2;
			unit.cooldown = 3.0;
			unit.speed = 0.0;
			unit.move_full = 1.0;
			unit.move_wait = 0.25;
			unit.area = 0.75;
			unit.range = 3.5;
			unit.length = 1.0;
			unit.health_bar_offset = (Vector2){0, CUP_SIZE * 3.5};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 0;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, CUP_SIZE * 0.5};
			break;
		case(UNIT_BASIC):
			unit.max_health = 8;
			unit.damage = 2;
			unit.cooldown = 1.0;
			unit.speed = 16.0;
			unit.move_full = 1.0;
			unit.move_wait = 0.25;
			unit.area = 1.0;
			unit.range = 1.0;
			unit.length = 1.0;
			unit.health_bar_offset = (Vector2){0, CUP_SIZE};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 0;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, 0};
			break;
		case(UNIT_TALL):
			unit.max_health = 16;
			unit.damage = 2;
			unit.cooldown = 1.2;
			unit.speed = 15.0;
			unit.move_full = 1.0;
			unit.move_wait = 0.30;
			unit.area = 2.0;
			unit.range = 1.0;
			unit.length = 1.0;
			unit.health_bar_offset = (Vector2){0, CUP_SIZE * 2};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 1;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, 0};
			unit.cups[1].active = true;
			unit.cups[1].pattern = 0;
			unit.cups[1].animation = 0;
			unit.cups[1].offset = (Vector2){0, CUP_SIZE};
			break;
		case(UNIT_THROWER):
			unit.max_health = 16;
			unit.damage = 2;
			unit.cooldown = 1.0;
			unit.speed = 14.0;
			unit.move_full = 1.0;
			unit.move_wait = 0.30;
			unit.area = 0.75;
			unit.range = 2.25;
			unit.length = 1.0;
			unit.health_bar_offset = (Vector2){0, CUP_SIZE * 2};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 0;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, 0};
			unit.cups[1].active = true;
			unit.cups[1].pattern = 1;
			unit.cups[1].animation = 0;
			unit.cups[1].offset = (Vector2){0, CUP_SIZE};
			break;
		case(UNIT_PILLAR):
			unit.max_health = 24;
			unit.damage = 2;
			unit.cooldown = 1.2;
			unit.speed = 14.5;
			unit.move_full = 1.0;
			unit.move_wait = 0.35;
			unit.area = 3.0;
			unit.range = 1.0;
			unit.length = 1.0;
			unit.health_bar_offset = (Vector2){0, CUP_SIZE * 3};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 0;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, 0};
			unit.cups[1].active = true;
			unit.cups[1].pattern = 1;
			unit.cups[1].animation = 0;
			unit.cups[1].offset = (Vector2){0, CUP_SIZE};
			unit.cups[2].active = true;
			unit.cups[2].pattern = 0;
			unit.cups[2].animation = 0;
			unit.cups[2].offset = (Vector2){0, CUP_SIZE * 2};
			break;
		case(UNIT_HORSE):
			unit.max_health = 24;
			unit.damage = 2;
			unit.cooldown = 0.5;
			unit.speed = 24.0;
			unit.move_full = 10.0;
			unit.move_wait = 0.0;
			unit.area = 1.0;
			unit.range = 1.0;
			unit.length = 2.0;
			unit.health_bar_offset = (Vector2){CUP_SIZE * 0.5, CUP_SIZE * 2};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 0;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, 0};
			unit.cups[1].active = true;
			unit.cups[1].pattern = 0;
			unit.cups[1].animation = 0;
			unit.cups[1].offset = (Vector2){CUP_SIZE, 0};
			unit.cups[2].active = true;
			unit.cups[2].pattern = 0;
			unit.cups[2].animation = 0;
			unit.cups[2].offset = (Vector2){CUP_SIZE * 0.5, CUP_SIZE};
			break;
		case(UNIT_CANNON):
			unit.max_health = 24;
			unit.damage = 5;
			unit.cooldown = 2.5;
			unit.speed = 7.5;
			unit.move_full = 10.0;
			unit.move_wait = 0.0;
			unit.area = 0.75;
			unit.range = 2.75;
			unit.length = 2.0;
			unit.health_bar_offset = (Vector2){CUP_SIZE * 0.5, CUP_SIZE * 2};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 0;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, 0};
			unit.cups[1].active = true;
			unit.cups[1].pattern = 0;
			unit.cups[1].animation = 0;
			unit.cups[1].offset = (Vector2){CUP_SIZE, 0};
			unit.cups[2].active = true;
			unit.cups[2].pattern = 1;
			unit.cups[2].animation = 0;
			unit.cups[2].offset = (Vector2){CUP_SIZE * 0.5, CUP_SIZE};
			break;
		case(UNIT_VETERAN):
			unit.max_health = 32;
			unit.damage = 2;
			unit.cooldown = 0.75;
			unit.speed = 18.0;
			unit.move_full = 1.0;
			unit.move_wait = 0.2;
			unit.area = 1.0;
			unit.range = 1.25;
			unit.length = 2.0;
			unit.health_bar_offset = (Vector2){CUP_SIZE * 0.5, CUP_SIZE * 2};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 1;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, 0};
			unit.cups[1].active = true;
			unit.cups[1].pattern = 0;
			unit.cups[1].animation = 0;
			unit.cups[1].offset = (Vector2){CUP_SIZE, 0};
			unit.cups[2].active = true;
			unit.cups[2].pattern = 0;
			unit.cups[2].animation = 0;
			unit.cups[2].offset = (Vector2){CUP_SIZE * 0.5, CUP_SIZE};
			break;
		case(UNIT_PIRATE):
			unit.max_health = 24;
			unit.damage = 2;
			unit.cooldown = 2.0;
			unit.speed = 20.0;
			unit.move_full = 1.0;
			unit.move_wait = 0.5;
			unit.area = 1.0;
			unit.range = 1.0;
			unit.length = 2.0;
			unit.health_bar_offset = (Vector2){CUP_SIZE * 0.5, CUP_SIZE * 2};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 1;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, 0};
			unit.cups[1].active = true;
			unit.cups[1].pattern = 0;
			unit.cups[1].animation = 0;
			unit.cups[1].offset = (Vector2){CUP_SIZE, 0};
			unit.cups[2].active = true;
			unit.cups[2].pattern = 1;
			unit.cups[2].animation = 0;
			unit.cups[2].offset = (Vector2){CUP_SIZE * 0.5, CUP_SIZE};
			break;
		case(UNIT_CLERIC):
			unit.max_health = 16;
			unit.damage = 1;
			unit.heal = 1;
			unit.cooldown = 0.5;
			unit.speed = 4.0;
			unit.move_full = 2.0;
			unit.move_wait = 0.5;
			unit.area = 0.25;
			unit.range = 3.0;
			unit.length = 2.0;
			unit.health_bar_offset = (Vector2){CUP_SIZE * 0.5, CUP_SIZE * 2};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 1;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, 0};
			unit.cups[1].active = true;
			unit.cups[1].pattern = 1;
			unit.cups[1].animation = 0;
			unit.cups[1].offset = (Vector2){CUP_SIZE, 0};
			unit.cups[2].active = true;
			unit.cups[2].pattern = 0;
			unit.cups[2].animation = 0;
			unit.cups[2].offset = (Vector2){CUP_SIZE * 0.5, CUP_SIZE};
			break;
		default:
			unit.max_health = 8;
			unit.damage = 2;
			unit.cooldown = 1.0;
			unit.speed = 16.0;
			unit.move_full = 1.0;
			unit.move_wait = 0.25;
			unit.area = 1.0;
			unit.range = 1.0;
			unit.length = 1.0;
			unit.health_bar_offset = (Vector2){0, 32};
			unit.cups[0].active = true;
			unit.cups[0].pattern = 0;
			unit.cups[0].animation = 0;
			unit.cups[0].offset = (Vector2){0, 0};
			unit.cups[1].active = false;
			unit.cups[2].active = false;
			unit.cups[3].active = false;
			unit.cups[4].active = false;
			break;
	}
	unit.health = unit.max_health;

	return unit;
}

void UnitMove(Unit* unit, float mult)
{
	if(unit->speed == 0.0)
	{
		return;
	}
	unit->move_time += FRAME;
	if(unit->move_time > unit->move_full)
	{
		unit->move_time = 0;
	}
	else if(unit->move_time > unit->move_wait)
	{
		unit->position.x += unit->direction * FRAME * unit->speed * mult;
	}
}

bool UnitDetectionRangeCheck(Unit* unit, Side* side, DetectionRangeCheckType type)
{
	Rectangle detect_range = UnitDetectionArea(*unit);
	bool detected = false;
	unit->enemy_distance = -1.0;
	for(int i = 0; i < MAX_UNITS; i++) 
	{
		Unit other = side->units[i];
		if(other.alive != 0) for(int j = 0; j < CUPS_PER_UNIT; j++)
		{
			if(other.cups[j].active)
			{
				Rectangle hitbox = CupHitbox(other, j);
				if(CheckCollisionRecs(detect_range, hitbox))
				{
					float distance = absf(unit->position.x - CupPosition(other, j).x) * CUP_SIZE_INV - unit->length + 1.0;
					if(distance > unit->range)
					{
						distance = unit->range; 
					}
					distance -= 1.0;
					if(distance < 0.0)
					{
						distance = 0.0;
					}
					if(unit->enemy_distance == -1.0)
					{
						unit->enemy_distance = distance;
					}
					if(type == CHECK_CLOSEST && distance < unit->enemy_distance)
					{
						unit->enemy_distance = distance;
					}
					if(type == CHECK_FURTHEST && distance > unit->enemy_distance)
					{
						unit->enemy_distance = distance;
					}
					//TraceLog(LOG_INFO, "Enemy dist: %f", unit->enemy_distance);
					detected = true;
				}
			}
		}
	}
	return detected;
}

bool UnitCanPass(Unit* unit, Unit* other)
{
	return other->idle_state != IDLE_STAND &&
		other->speed < unit->speed && (
		other->state == STATE_MOVE ||
		other->state == STATE_IDLE ||
		other->state == STATE_HEAL_COOLDOWN ||
		other->state == STATE_HEAL_START ||
		other->state == STATE_HEAL_END
		);
}

bool CupOverlapsUnit(Unit* unit, Rectangle hitbox)
{
	for(int i = 0; i < CUPS_PER_UNIT; i++)
	{
		if(unit->cups[i].active)
		{
			Rectangle unitbox = CupHitbox(*unit, i);
			if(CheckCollisionRecs(unitbox, hitbox))
			{
				return true;
			}
		}
	}
	return false;
}

char UnitFrontCheck(Unit* unit, Side* side)
{
	Rectangle detect_range = UnitFrontArea(*unit);
	char result = IDLE_STOP;
	for(int i = 0; i < MAX_UNITS; i++) 
	{
		Unit other = side->units[i];
		if(other.alive != 0 && !UnitCanPass(unit, &other)) for(int j = 0; j < CUPS_PER_UNIT; j++)
		{
			if(other.cups[j].active)
			{
				Rectangle hitbox = CupHitbox(other, j);
				if(CheckCollisionRecs(detect_range, hitbox))
				{
					result = IDLE_STAND;
					if(CupOverlapsUnit(unit, hitbox))
					{
						return IDLE_BACKUP;
					}
				}
			}
		}
	}
	return result;
}

void UnitAttack(Unit* unit, Side* side)
{
	Rectangle hurtbox = UnitAttackArea(*unit);
	for(int i = 0; i < MAX_UNITS; i++) 
	{
		Unit other = side->units[i];
		if(other.alive != 0) for(int j = 0; j < CUPS_PER_UNIT; j++)
		{
			if(other.cups[j].active)
			{
				Rectangle hitbox = CupHitbox(other, j);
				if(CheckCollisionRecs(hurtbox, hitbox))
				{
					side->units[i].incoming += unit->damage;
				}
			}
		}
	}
}

void UnitHeal(Unit* unit, Side* side)
{
	Rectangle hurtbox = UnitAttackArea(*unit);
	for(int i = 0; i < MAX_UNITS; i++) 
	{
		Unit other = side->units[i];
		if(other.alive != 0) for(int j = 0; j < CUPS_PER_UNIT; j++)
		{
			if(other.cups[j].active)
			{
				Rectangle hitbox = CupHitbox(other, j);
				if(CheckCollisionRecs(hurtbox, hitbox))
				{
					side->units[i].incoming -= unit->heal;
					return;
				}
			}
		}
	}
}

void UnitProcess(Unit* unit, Side* enemy_side, Side* friend_side)
{
	if(unit->alive == 0)
	{
		return;
	}
	switch(unit->state)
	{
		case STATE_MOVE:
			UnitMove(unit, 1.0);
			break;
		case STATE_IDLE:
			if(unit->idle_state == IDLE_BACKUP)
			{
				UnitMove(unit, -1.0);
			}
			break;
		case STATE_COOLDOWN:
			break;
		case STATE_ATTACK_START:
			break;
		case STATE_ATTACK_END:
			break;
		case STATE_HEAL_COOLDOWN:
			break;
		case STATE_HEAL_START:
			break;
		case STATE_HEAL_END:
			break;
		case STATE_DEATH:
			break;
	}
	
	unit->state_time -= FRAME;
	if(unit->state_time <= 0.0)
	{
		// STATE END
		if(unit->state == STATE_ATTACK_START)
		{
			//TraceLog(LOG_INFO, "Attack");
			UnitAttack(unit, enemy_side);
		}
		if(unit->state == STATE_HEAL_START)
		{
			UnitHeal(unit, friend_side);
		}
		if(unit->state == STATE_DEATH)
		{
			unit->state = STATE_NULL;
			unit->alive = 0;
		}
		// CHANGE STATE
		switch(unit->state)
		{
			case STATE_COOLDOWN:
				unit->state = STATE_MOVE;
				break;
			case STATE_HEAL_COOLDOWN:
				unit->state = STATE_MOVE;
				break;
			case STATE_ATTACK_START:
				unit->state = STATE_ATTACK_END;
				break;
			case STATE_ATTACK_END:
				unit->state = STATE_COOLDOWN;
				break;
			case STATE_HEAL_START:
				unit->state = STATE_HEAL_END;
				break;
			case STATE_HEAL_END:
				unit->state = STATE_HEAL_COOLDOWN;
				break;
		}
		if(unit->state == STATE_MOVE || unit->state == STATE_IDLE)
		{
			if(unit->heal > 0 && UnitDetectionRangeCheck(unit, friend_side, CHECK_FURTHEST))
			{
				unit->state = STATE_HEAL_START;
			}
			else if(unit->damage >= 0 && UnitDetectionRangeCheck(unit, enemy_side, CHECK_CLOSEST))
			{
				unit->state = STATE_ATTACK_START;
			}
			else 
			{
				char result = UnitFrontCheck(unit, friend_side);
				if(result)
				{
					unit->state = STATE_IDLE;
					unit->idle_state = result;
				}
				else
				{
					unit->state = STATE_MOVE;
				}
			}
		}
		// STATE START
		if(unit->state == STATE_MOVE)
		{
			unit->idle_state = IDLE_STOP;
		}
		switch(unit->state)
		{
			case STATE_NULL:
				unit->state_time = 1.0;
				break;
			case STATE_MOVE:
				unit->state_time = 0.1;
				break;
			case STATE_IDLE:
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
			case STATE_HEAL_COOLDOWN:
				unit->state_time = unit->cooldown;
				break;
			case STATE_HEAL_START:
				unit->state_time = 0.25;
				break;
			case STATE_HEAL_END:
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
	if(unit->health > unit->max_health)
	{
		unit->health = unit->max_health;
	}
	if(unit->health <= 0)
	{
		unit->state = STATE_DEATH;
		unit->state_time = 1.0;
	}
	//TraceLog(LOG_INFO, "%i", unit->health);
}

Side SideInit(Vector2 start_pos, char direction)
{
	Side side = (Side){0};
	side.spawn_position = start_pos;
	side.direction = direction;
	side.current_unit = 0;
	SpawnUnit(UNIT_BASE, &side);
	return side;
}

bool SpawnUnit(int type, Side* side)
{
	int reps = 0;
	while(reps < MAX_UNITS && side->units[side->current_unit].alive)
	{
		side->current_unit++;
		reps++;
		if(side->current_unit == MAX_UNITS)
		{
			side->current_unit = 1;
		}
	}
	if(reps < MAX_UNITS)
	{
		side->units[side->current_unit] = MakeUnit(type, side->spawn_position, side->direction);
		return true;
	}
	else
	{
		return false;
	}
}

char BaseAlive(Side* side)
{
	return side->units[0].alive;
}

void DrawUnitDebug(Unit unit)
{
	if(unit.alive == 0)
	{
		return;
	}
	if(unit.state == STATE_MOVE || unit.state == STATE_IDLE)
	{
		DrawRectangleRec(UnitDetectionArea(unit), TRANS_PURPLE);
	}
	if(unit.state == STATE_IDLE)
	{
		DrawRectangleRec(UnitFrontArea(unit), TRANS_BLUE);
	}
	for(int i = 0; i < CUPS_PER_UNIT; i++)
	{
		if(unit.cups[i].active)
		{
			Color color = GRAY;
			if(unit.cups[i].pattern == 1)
			{
				color = BLACK;
			}
			DrawRectangleRec(CupHitbox(unit, i), color);
		}
	}
	DrawPixel(unit.position.x, unit.position.y, GREEN);
}

void DrawUnitDebugAttack(Unit unit)
{
	if(unit.alive == 0)
	{
		return;
	}
	if(unit.state == STATE_ATTACK_START)
	{
		DrawRectangleRec(UnitAttackArea(unit), TRANS_RED);
	}
	if(unit.state == STATE_HEAL_START)
	{
		DrawRectangleRec(UnitAttackArea(unit), TRANS_GREEN);
	}
}

void DrawHealthBar(Unit unit)
{
	if(unit.alive == 0)
	{
		return;
	}
	Vector2 pos = unit.position;
	pos.x += CUP_SIZE * -0.5 + unit.health_bar_offset.x * unit.direction;
	pos.y -= 8 + unit.health_bar_offset.y;
	DrawRectangle(pos.x, pos.y, CUP_SIZE, 4, RED);
	DrawRectangle(pos.x, pos.y, CUP_SIZE * ((float)unit.health / (float)unit.max_health), 4, GREEN);
}
