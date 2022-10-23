#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 operator/(const float& value) const
	{
		Vector2 temp;
		temp.x = x / value;
		temp.y = y / value;

		return temp;
	}

	Vector2 operator+(const Vector2& other) const
	{
		Vector2 temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;

		return temp;
	}

	Vector2 operator-(const Vector2& other) const
	{
		Vector2 temp;
		temp.x = this->x - other.x;
		temp.y = this->y - other.y;

		return temp;
	}

	Vector2 operator* (const float& value) const
	{
		Vector2 temp;
		temp.x = this->x * value;
		temp.y = this->y * value;

		return temp;
	}

	Vector2 operator += (const Vector2& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vector2 operator -= (const Vector2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vector2(const Vector2& other) = default;
	Vector2() = default;
	~Vector2() = default;
};

typedef Vector2 Vector2D;
typedef Vector2 Pos;