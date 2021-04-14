#include "DXUT.h"
#include "Timer.h"

bool Timer::Update()
{
	start += D_TIME;
	if (start >= delay)
	{
		start = 0;
		return true;
	}
	return false;
}
