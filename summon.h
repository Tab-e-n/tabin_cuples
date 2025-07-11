#ifndef CUPSUMMON
#define CUPSUMMON

#include <raylib.h>
#include <raymath.h>
#include "cuplib.h"
#include "units.h"


#define GRID_SIZE (Vector2){10, 5}
#define GRID_AMOUNT 50		// GRID_SIZE.x * GRID_SIZE.y
#define CUPS_PER_STRUCTURE 8


typedef struct Structure
{
	unsigned char cups_present, 
		      grid[GRID_AMOUNT];
} Structure;

typedef struct UnitCode
{
	unsigned char codes[CUPS_PER_STRUCTURE];
	// 000000 0     0
	// pos    hi/lo placed
} UnitCode;


Structure StructureInit(void);

Vector2 StructureMousePos(Vector2 screen_pos, float scale, Vector2 mouse_pos);
int StructureCupGridID(Vector2 pos);
bool StructureFlipCup(Structure* structure, int id);
bool StructureAddCup(Structure* structure, Vector2 pos, unsigned char cup);
bool StructureRemoveCup(Structure* structure, Vector2 pos);

unsigned char StructureCupToCode(unsigned char type, int cup, int start_cup);
UnitCode InterpretPlayerStructure(Structure structure);

bool UnitCodeStart(unsigned char code);
bool UnitCodeContinue(unsigned char code);
int SpawnUnitFromCode(UnitCode unit, Side* side);

void DrawStructureGrid(Vector2 pos, float scale);
void DrawStructureDebug(Structure structure, Vector2 pos, float scale);


#endif
