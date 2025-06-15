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

typedef struct UnitCode
{
	char codes[CUPS_PER_UNIT];
	// 000000 0     0
	// pos    hi/lo placed
} UnitCode;


Structure StructureInit(void);

Vector2 StructureMousePos(Vector2 screen_pos, float scale, Vector2 mouse_pos);
int StructureCupGridID(Vector2 pos);
bool StructureFlipCup(Structure* structure, int id);
bool StructureAddCup(Structure* structure, Vector2 pos, char cup);
bool StructureRemoveCup(Structure* structure, Vector2 pos);

char StructureCupToCode(Structure structure, int cup, int start_cup);
UnitCode InterpretPlayerStructure(Structure structure);

bool UnitCodeStart(char code);
bool UnitCodeContinue(char code);
void SpawnUnitFromCode(UnitCode unit, Side* side);

void DrawStructureGrid(Vector2 pos, float scale);
void DrawStructureDebug(Structure structure, Vector2 pos, float scale);


#endif
