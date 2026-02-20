#include "Vector4.h"
#include "MathUtils.h"

float Vector4::LengthSqr() const
{
    return (x * x + y * y + z * z + w * w);
}

float Vector4::Length() const
{
    return (MathUtils::Sqrt(LengthSqr()));
}

void Vector4::Normalize()
{
    float len = Length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;
}
