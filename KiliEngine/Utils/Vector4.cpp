#include "Vector4.h"
#include "Maths.h"

float Vector4::LengthSqr() const
{
    return (x * x + y * y + z * z + w * w);
}

float Vector4::Length() const
{
    return (Maths::Sqrt(LengthSqr()));
}

void Vector4::Normalize()
{
    float len = Length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;
}
