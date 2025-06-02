#ifndef CUPSUMMON
#define CUPSUMMON

#include <raylib.h>
#include <raymath.h>
#include "cuplib.h"
#include "units.h"


#define GRID_SIZE (Vector2){10, 5}
#define GRID_AMOUNT 50		// GRID_SIZE.x * GRID_SIZE.y


typedef struct Structure
{
	char cups_present,
	     grid[GRID_AMOUNT];
} Structure;


Structure StructureInit(void);

Vector2 StructureMousePos(Vector2 screen_pos, float scale, Vector2 mouse_pos);
int StructureCupGridID(Vector2 pos);
bool StructureAddCup(Structure* structure, Vector2 pos, char cup);
bool StructureRemoveCup(Structure* structure, Vector2 pos);

UnitType InterpretPlayerStructure(Structure structure);

void DrawStructureGrid(Vector2 pos, float scale);
void DrawStructureDebug(Structure structure, Vector2 pos, float scale);


#endif
