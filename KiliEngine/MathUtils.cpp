#include "MathUtils.h"

bool MathUtils::NearlyEqual(const float a, const float b)
{
	return NearZero(a-b);
}
