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

void DrawUnitDebug(Unit unit)
{
	DrawRectangleRec(UnitDetectionArea(unit), PURPLE);
	DrawRectangle(unit.position.x - CUP_SIZE * 0.5, unit.position.y - CUP_SIZE, CUP_SIZE, CUP_SIZE, BLACK);
	DrawRectangleRec(UnitAttackArea(unit), RED);
}
