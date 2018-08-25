#include <iostream>
#include <string>
#include <cmath>
#include "GLEngine/math/Vec3f.hpp"
#include "GLEngine/math/Vec2f.hpp"

namespace GLEngine
{
	float Vec3f::Magnitude()
	{
		return std::sqrt(pow(x, 2) + pow(y, 2));
	}

	/* Vector Vector Add Functions */
	Vec3f Vec3f::Add(const Vec3f& b)
	{
		Vec3f vec(this->x + b.x, this->y + b.y);
		return vec;
	}

	void Vec3f::AddEquals(const Vec3f& b)
	{
		this->x += b.x;
		this->y += b.y;
	}

	Vec3f Vec3f::operator+(const Vec3f& b)
	{
		Vec3f vec(this->x + b.x, this->y + b.y);
		return vec;
	}

	void Vec3f::operator+=(const Vec3f& b)
	{
		this->x += b.x;
		this->y += b.y;
	}

	/* Scalar Add Functions */
	Vec3f Vec3f::Add(float b)
	{
		Vec3f vec(this->x + b, this->y + b);
		return vec;
	}

	void Vec3f::AddEquals(float b)
	{
		this->x += b;
		this->y += b;
	}

	Vec3f Vec3f::operator+(float b)
	{
		Vec3f vec(this->x + b, this->y + b);
		return vec;
	}

	void Vec3f::operator+=(float b)
	{
		this->x += b;
		this->y += b;
	}

	/* Vector Vector Sub Functions */
	Vec3f Vec3f::Sub(const Vec3f& b)
	{
		Vec3f vec(this->x - b.x, this->y - b.y);
		return vec;
	}

	void Vec3f::SubEquals(const Vec3f& b)
	{
		this->x -= b.x;
		this->y -= b.y;
	}

	Vec3f Vec3f::operator-(const Vec3f& b)
	{
		Vec3f vec(this->x - b.x, this->y - b.y);
		return vec;
	}

	void Vec3f::operator-=(const Vec3f& b)
	{
		this->x -= b.x;
		this->y -= b.y;
	}

	/* Scalar Sub Functions */
	Vec3f Vec3f::Sub(float b)
	{
		Vec3f vec(this->x - b, this->y - b);
		return vec;
	}

	void Vec3f::SubEquals(float b)
	{
		this->x -= b;
		this->y -= b;
	}

	Vec3f Vec3f::operator-(float b)
	{
		Vec3f vec(this->x - b, this->y - b);
		return vec;
	}

	void Vec3f::operator-=(float b)
	{
		this->x -= b;
		this->y -= b;
	}

	/* Vector Vector Mult Functions */
	Vec3f Vec3f::Mult(const Vec3f& b)
	{
		Vec3f vec(this->x * b.x, this->y * b.y);
		return vec;
	}

	void Vec3f::MultEquals(const Vec3f& b)
	{
		this->x *= b.x;
		this->y *= b.y;
	}

	Vec3f Vec3f::operator*(const Vec3f& b)
	{
		Vec3f vec(this->x * b.x, this->y * b.y);
		return vec;
	}

	void Vec3f::operator*=(const Vec3f& b)
	{
		this->x *= b.x;
		this->y *= b.y;
	}

	/* Scalar Mult Functions */
	Vec3f Vec3f::Mult(float b)
	{
		Vec3f vec(this->x * b, this->y * b);
		return vec;
	}

	void Vec3f::MultEquals(float b)
	{
		this->x *= b;
		this->y *= b;
	}

	Vec3f Vec3f::operator*(float b)
	{
		Vec3f vec(this->x * b, this->y * b);
		return vec;
	}

	void Vec3f::operator*=(float b)
	{
		this->x *= b;
		this->y *= b;
	}

	/* Vector Vector Div Functions */
	Vec3f Vec3f::Div(const Vec3f& b)
	{
		Vec3f vec(this->x / b.x, this->y / b.y);
		return vec;
	}

	void Vec3f::DivEquals(const Vec3f& b)
	{
		this->x /= b.x;
		this->y /= b.y;
	}

	Vec3f Vec3f::operator/(const Vec3f& b)
	{
		Vec3f vec(this->x / b.x, this->y / b.y);
		return vec;
	}

	void Vec3f::operator/=(const Vec3f& b)
	{
		this->x /= b.x;
		this->y /= b.y;
	}

	/* Scalar Div Functions */
	Vec3f Vec3f::Div(float b)
	{
		Vec3f vec(this->x / b, this->y / b);
		return vec;
	}

	void Vec3f::DivEquals(float b)
	{
		this->x /= b;
		this->y /= b;
	}

	Vec3f Vec3f::operator/(float b)
	{
		Vec3f vec(this->x / b, this->y / b);
		return vec;
	}

	void Vec3f::operator/=(float b)
	{
		this->x /= b;
		this->y /= b;
	}

	/* Misc */
	std::string Vec3f::to_string()
	{
		return "["+std::to_string(this->x)+", "+std::to_string(this->y)+", "+std::to_string(this->z)+"]";
	}
}
