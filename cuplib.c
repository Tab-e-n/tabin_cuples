#include <raylib.h>
#include "cuplib.h"

float absf(float x)
{
	return x < 0.0 ? -x : x;
}

float maxf(float x, float y)
{
	return x > y ? x : y;
}

float minf(float x, float y)
{
	return x < y ? x : y;
}
