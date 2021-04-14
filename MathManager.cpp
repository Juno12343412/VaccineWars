#include "DXUT.h"
#include "MathManager.h"

void MathManager::FloodFill(int x, int z)
{
	if (OBJECT->map[x][z] == 0 || OBJECT->map[x][z] == 7 || OBJECT->map[x][z] == 10)
	{
		OBJECT->map[x][z] = 2;
		FloodFill(x + 1, z);
		FloodFill(x - 1, z);
		FloodFill(x, z + 1);
		FloodFill(x, z - 1);
	}
}

void MathManager::SearchFloodFill(int x, int z, int& bossCount)
{
	if (OBJECT->map[x][z] == 4)
	{
		bossCount++;
		return;
	}
	if (OBJECT->map[x][z] == 0 || OBJECT->map[x][z] == 10)
	{
		if(OBJECT->map[x][z] == 0)
			OBJECT->map[x][z] = 5;
		else if(OBJECT->map[x][z] == 10)
			OBJECT->map[x][z] = 11;

		SearchFloodFill(x + 1, z, bossCount);
		SearchFloodFill(x - 1, z, bossCount);
		SearchFloodFill(x, z + 1, bossCount);
		SearchFloodFill(x, z - 1, bossCount);
	}
}

void MathManager::BackFloodFill(int x, int z)
{
	if (OBJECT->map[x][z] == 1)
	{
		OBJECT->map[x][z] = 6;
		BackFloodFill(x + 1, z);
		BackFloodFill(x - 1, z);
		BackFloodFill(x, z + 1);
		BackFloodFill(x, z - 1);
	}
}
