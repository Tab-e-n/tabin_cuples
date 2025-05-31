#ifndef CUPSUMMON
#define CUPSUMMON

#include <raylib.h>
#include "cuplib.h"
#include "units.h"


typedef struct Structure
{
	char cup_grid[25];
} Structure;


Structure StructureInit(void);
bool StructureAddCup(Structure structure, Vector2 pos);
bool StructureRemoveCup(Structure structure, Vector2 pos);

UnitType InterpretPlayerStructure(Structure structure);


#endif
