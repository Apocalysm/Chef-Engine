#include "Math.h"

using ce::Math;

Math::Math()
{
}


Math::~Math()
{
}

float ce::Math::ClampF(float value, float maxValue, float minValue)
{
	if (value > maxValue)
	{
		value = maxValue;
	}
	else if (value < minValue)
	{
		value = minValue;
	}

	return value;
}

int ce::Math::ClampI(int value, int maxValue, int minValue)
{
	return 0;
}

float ce::Math::Lerp(float value, float goal, float step)
{
    return value + ((goal - value) * step);
}
