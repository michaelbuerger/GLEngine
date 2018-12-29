#include <iostream>
#include <string>
#include <cmath>
#include "GLEngine/math/Vec2f.hpp"

namespace GLEngine
{
	Vec2f::Vec2f()
		: x(0)
		, y(0)
	{ }

	Vec2f::Vec2f(float x, float y)
		: x(x)
		, y(y)
	{ }

	Vec2f::Vec2f(const Vec2f& v)
		: x(v.x)
		, y(v.y)
	{ }

	float Vec2f::Magnitude()
	{
		return std::sqrt(pow(x, 2) + pow(y, 2));
	}

	/* Vector Vector Add Functions */
	Vec2f Vec2f::Add(const Vec2f& b)
	{
		Vec2f vec(this->x + b.x, this->y + b.y);
		return vec;
	}

	void Vec2f::AddEquals(const Vec2f& b)
	{
		this->x += b.x;
		this->y += b.y;
	}

	Vec2f Vec2f::operator+(const Vec2f& b)
	{
		Vec2f vec(this->x + b.x, this->y + b.y);
		return vec;
	}

	void Vec2f::operator+=(const Vec2f& b)
	{
		this->x += b.x;
		this->y += b.y;
	}

	/* Scalar Add Functions */
	Vec2f Vec2f::Add(float b)
	{
		Vec2f vec(this->x + b, this->y + b);
		return vec;
	}

	void Vec2f::AddEquals(float b)
	{
		this->x += b;
		this->y += b;
	}

	Vec2f Vec2f::operator+(float b)
	{
		Vec2f vec(this->x + b, this->y + b);
		return vec;
	}

	void Vec2f::operator+=(float b)
	{
		this->x += b;
		this->y += b;
	}

	/* Vector Vector Sub Functions */
	Vec2f Vec2f::Sub(const Vec2f& b)
	{
		Vec2f vec(this->x - b.x, this->y - b.y);
		return vec;
	}

	void Vec2f::SubEquals(const Vec2f& b)
	{
		this->x -= b.x;
		this->y -= b.y;
	}

	Vec2f Vec2f::operator-(const Vec2f& b)
	{
		Vec2f vec(this->x - b.x, this->y - b.y);
		return vec;
	}

	void Vec2f::operator-=(const Vec2f& b)
	{
		this->x -= b.x;
		this->y -= b.y;
	}

	/* Scalar Sub Functions */
	Vec2f Vec2f::Sub(float b)
	{
		Vec2f vec(this->x - b, this->y - b);
		return vec;
	}

	void Vec2f::SubEquals(float b)
	{
		this->x -= b;
		this->y -= b;
	}

	Vec2f Vec2f::operator-(float b)
	{
		Vec2f vec(this->x - b, this->y - b);
		return vec;
	}

	void Vec2f::operator-=(float b)
	{
		this->x -= b;
		this->y -= b;
	}

	/* Vector Vector Mult Functions */
	Vec2f Vec2f::Mult(const Vec2f& b)
	{
		Vec2f vec(this->x * b.x, this->y * b.y);
		return vec;
	}

	void Vec2f::MultEquals(const Vec2f& b)
	{
		this->x *= b.x;
		this->y *= b.y;
	}

	Vec2f Vec2f::operator*(const Vec2f& b)
	{
		Vec2f vec(this->x * b.x, this->y * b.y);
		return vec;
	}

	void Vec2f::operator*=(const Vec2f& b)
	{
		this->x *= b.x;
		this->y *= b.y;
	}

	/* Scalar Mult Functions */
	Vec2f Vec2f::Mult(float b)
	{
		Vec2f vec(this->x * b, this->y * b);
		return vec;
	}

	void Vec2f::MultEquals(float b)
	{
		this->x *= b;
		this->y *= b;
	}

	Vec2f Vec2f::operator*(float b)
	{
		Vec2f vec(this->x * b, this->y * b);
		return vec;
	}

	void Vec2f::operator*=(float b)
	{
		this->x *= b;
		this->y *= b;
	}

	/* Vector Vector Div Functions */
	Vec2f Vec2f::Div(const Vec2f& b)
	{
		Vec2f vec(this->x / b.x, this->y / b.y);
		return vec;
	}

	void Vec2f::DivEquals(const Vec2f& b)
	{
		this->x /= b.x;
		this->y /= b.y;
	}

	Vec2f Vec2f::operator/(const Vec2f& b)
	{
		Vec2f vec(this->x / b.x, this->y / b.y);
		return vec;
	}

	void Vec2f::operator/=(const Vec2f& b)
	{
		this->x /= b.x;
		this->y /= b.y;
	}

	/* Scalar Div Functions */
	Vec2f Vec2f::Div(float b)
	{
		Vec2f vec(this->x / b, this->y / b);
		return vec;
	}

	void Vec2f::DivEquals(float b)
	{
		this->x /= b;
		this->y /= b;
	}

	Vec2f Vec2f::operator/(float b)
	{
		Vec2f vec(this->x / b, this->y / b);
		return vec;
	}

	void Vec2f::operator/=(float b)
	{
		this->x /= b;
		this->y /= b;
	}

	/* Misc */
	std::string Vec2f::ToString()
	{
		return "["+std::to_string(this->x)+", "+std::to_string(this->y)+"]";
	}
}
