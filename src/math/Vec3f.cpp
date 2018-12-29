#include <iostream>
#include <string>
#include <cmath>
#include "GLEngine/math/Vec3f.hpp"

namespace GLEngine
{
	Vec3f::Vec3f()
		: x(0)
		, y(0)
		, z(0)
	{ }

	Vec3f::Vec3f(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{ }

	Vec3f::Vec3f(const Vec3f& v)
		: x(v.x)
		, y(v.y)
		, z(v.z)
	{ }

	float Vec3f::Magnitude()
	{
		return std::sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	/* Vector Vector Add Functions */
	Vec3f Vec3f::Add(const Vec3f& b)
	{
		Vec3f vec(this->x + b.x, this->y + b.y, this->z + b.z);
		return vec;
	}

	void Vec3f::AddEquals(const Vec3f& b)
	{
		this->x += b.x;
		this->y += b.y;
		this->z += b.z;
	}

	Vec3f Vec3f::operator+(const Vec3f& b)
	{
		return this->Add(b);
	}

	void Vec3f::operator+=(const Vec3f& b)
	{
		this->AddEquals(b);
	}

	/* Scalar Add Functions */
	Vec3f Vec3f::Add(float b)
	{
		Vec3f vec(this->x + b, this->y + b, this->z + b);
		return vec;
	}

	void Vec3f::AddEquals(float b)
	{
		this->x += b;
		this->y += b;
		this->z += b;
	}

	Vec3f Vec3f::operator+(float b)
	{
		return this->Add(b);
	}

	void Vec3f::operator+=(float b)
	{
		this->AddEquals(b);
	}

	/* Vector Vector Sub Functions */
	Vec3f Vec3f::Sub(const Vec3f& b)
	{
		Vec3f vec(this->x - b.x, this->y - b.y, this->z - b.z);
		return vec;
	}

	void Vec3f::SubEquals(const Vec3f& b)
	{
		this->x -= b.x;
		this->y -= b.y;
		this->z -= b.z;
	}

	Vec3f Vec3f::operator-(const Vec3f& b)
	{
		return this->Sub(b);
	}

	void Vec3f::operator-=(const Vec3f& b)
	{
		this->SubEquals(b);
	}

	/* Scalar Sub Functions */
	Vec3f Vec3f::Sub(float b)
	{
		Vec3f vec(this->x - b, this->y - b, this->z - b);
		return vec;
	}

	void Vec3f::SubEquals(float b)
	{
		this->x -= b;
		this->y -= b;
		this->z -= b;
	}

	Vec3f Vec3f::operator-(float b)
	{
		return this->Sub(b);
	}

	void Vec3f::operator-=(float b)
	{
		this->SubEquals(b);
	}

	/* Vector Vector Mult Functions */
	Vec3f Vec3f::Mult(const Vec3f& b)
	{
		Vec3f vec(this->x * b.x, this->y * b.y, this->z * b.z);
		return vec;
	}

	void Vec3f::MultEquals(const Vec3f& b)
	{
		this->x *= b.x;
		this->y *= b.y;
		this->z *= b.z;
	}

	Vec3f Vec3f::operator*(const Vec3f& b)
	{
		return this->Mult(b);
	}

	void Vec3f::operator*=(const Vec3f& b)
	{
		this->MultEquals(b);
	}

	/* Scalar Mult Functions */
	Vec3f Vec3f::Mult(float b)
	{
		Vec3f vec(this->x * b, this->y * b, this->z * b);
		return vec;
	}

	void Vec3f::MultEquals(float b)
	{
		this->x *= b;
		this->y *= b;
		this->z *= b;
	}

	Vec3f Vec3f::operator*(float b)
	{
		return this->Mult(b);
	}

	void Vec3f::operator*=(float b)
	{
		this->MultEquals(b);
	}

	/* Vector Vector Div Functions */
	Vec3f Vec3f::Div(const Vec3f& b)
	{
		Vec3f vec(this->x / b.x, this->y / b.y, this->z / b.z);
		return vec;
	}

	void Vec3f::DivEquals(const Vec3f& b)
	{
		this->x /= b.x;
		this->y /= b.y;
		this->z /= b.z;
	}

	Vec3f Vec3f::operator/(const Vec3f& b)
	{
		return this->Div(b);
	}

	void Vec3f::operator/=(const Vec3f& b)
	{
		this->DivEquals(b);
	}

	/* Scalar Div Functions */
	Vec3f Vec3f::Div(float b)
	{
		Vec3f vec(this->x / b, this->y / b, this->z / b);
		return vec;
	}

	void Vec3f::DivEquals(float b)
	{
		this->x /= b;
		this->y /= b;
		this->z /= b;
	}

	Vec3f Vec3f::operator/(float b)
	{
		return this->Div(b);
	}

	void Vec3f::operator/=(float b)
	{
		this->DivEquals(b);
	}

	/* Misc */
	std::string Vec3f::ToString()
	{
		return "["+std::to_string(this->x)+", "+std::to_string(this->y)+", "+std::to_string(this->z)+"]";
	}
}
