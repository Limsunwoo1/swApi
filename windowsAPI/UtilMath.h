#pragma once
#include "Maths.h"
#include <math.h>

#define PI 3.141592

namespace sw
{
    inline float Length(const Vector2& pos)
    {
        return sqrtf((pos.x * pos.x) + (pos.y * pos.y));
    }

    inline float ToRadian(float Degree)
    {
        return Degree * (PI / 180.f);
    }

    inline float ToDegree(float Radian)
    {
        return Radian * (180.f / PI);
    }

    inline float Sin(float Degree)
    {
        return sinf(ToRadian(Degree));
    }

    inline float Cos(float Degree)
    {
        return cosf(ToRadian(Degree));
    }

    inline Vector2 Normalize(const Vector2& Invec)
    {
        // ������ ���̸� ���ϰ� �� ���Ҹ� ���̷� ������ �ش�
        // ������ ����ȭ, ���� ����
        float length = Length(Invec);

        if (length != 0)
            return Vector2(Invec.x / length, Invec.y / length);
        else
            return Vector2(0.0f, 0.0f);
    }
}