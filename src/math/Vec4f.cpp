#include <iostream>
#include <string>
#include <cmath>
#include "GLEngine/math/Vec4f.hpp"

namespace GLEngine
{
	Vec4f::Vec4f()
	: x(0),
		y(0),
		z(0),
		w(0)
	{ }

	Vec4f::Vec4f(float x, float y, float z, float w)
	: x(x),
		y(y),
		z(z),
		w(w)
	{ }

	Vec4f::Vec4f(const Vec4f& v)
	: x(v.x),
		y(v.y),
		z(v.z),
		w(v.w)
	{ }

	float Vec4f::Magnitude()
	{
		return std::sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
	}

	/* Vector Vector Add Functions */
	Vec4f Vec4f::Add(const Vec4f& b)
	{
		Vec3f vec(this->x + b.x, this->y + b.y, this->z + b.z, this->w + b.w);
		return vec;
	}

	void Vec4f::AddEquals(const Vec4f& b)
	{
		this->x += b.x;
		this->y += b.y;
		this->z += b.z;
		this->w += b.w;
	}

	Vec4f Vec4f::operator+(const Vec4f& b)
	{
		return this->Add(b);
	}

	void Vec4f::operator+=(const Vec4f& b)
	{
		this->AddEquals(b);
	}

	/* Scalar Add Functions */
	Vec4f Vec4f::Add(float b)
	{
		Vec4f vec(this->x + b, this->y + b, this->z + b, this->w + b);
		return vec;
	}

	void Vec4f::AddEquals(float b)
	{
		this->x += b;
		this->y += b;
		this->z += b;
		this->w += b;
	}

	Vec4f Vec4f::operator+(float b)
	{
		return this->Add(b);
	}

	void Vec4f::operator+=(float b)
	{
		this->AddEquals(b);
	}

	/* Vector Vector Sub Functions */
	Vec4f Vec4f::Sub(const Vec4f& b)
	{
		Vec4f vec(this->x - b.x, this->y - b.y, this->z - b.z, this->w - b.w);
		return vec;
	}

	void Vec4f::SubEquals(const Vec4f& b)
	{
		this->x -= b.x;
		this->y -= b.y;
		this->z -= b.z;
		this->w -= b.w;
	}

	Vec4f Vec4f::operator-(const Vec4f& b)
	{
		return this->Sub(b);
	}

	void Vec4f::operator-=(const Vec4f& b)
	{
		this->SubEquals(b);
	}

	/* Scalar Sub Functions */

	Vec4f Vec4f::operator/(const Vec4f&
	Vec4f Vec4f::Sub(float b)
	{
		Vec4f vec(this->x - b, this->y - b, this->z - b, this->w - b);
		return vec;
	}

	void Vec4f::SubEquals(float b)
	{
		this->x -= b;
		this->y -= b;
		this->z -= b;
		this->w -= b;
	}

	Vec4f Vec4f::operator-(float b)
	{
		return this->Sub(b);
	}

	void Vec4f::operator-=(float b)
	{
		this->SubEquals(b);
	}

	/* Vector Vector Mult Functions */
	Vec4f Vec4f::Mult(const Vec4f& b)
	{
		Vec4f vec(this->x * b.x, this->y * b.y, this->z * b.z, this->w * b.w);
		return vec;
	}

	void Vec4f::MultEquals(const Vec4f& b)
	{
		this->x *= b.x;
		this->y *= b.y;
		this->z *= b.z;
		this->w *= b.w;
	}

	Vec4f Vec4f::operator*(const Vec4f& b)
	{
		return this->Mult(b);
	}

	void Vec4f::operator*=(const Vec4f& b)
	{
		this->MultEquals(b);
	}

	/* Scalar Mult Functions */
	Vec4f Vec4f::Mult(float b)
	{
		Vec4f vec(this->x * b, this->y * b, this->z * b, this->w * b);
		return vec;
	}

	void Vec4f::MultEquals(float b)
	{
		this->x *= b;
		this->y *= b;
		this->z *= b;
		this->w *= b;
	}

	Vec4f Vec4f::operator*(float b)
	{
		return this->Mult(b);
	}

	void Vec4f::operator*=(float b)
	{
		this->MultEquals(b);
	}

	/* Vector Vector Div Functions */
	Vec4f Vec4f::Div(const Vec4f& b)
	{
		Vec4f vec(this->x / b.x, this->y / b.y, this->z / b.z, this->w / b.w);
		return vec;
	}

	void Vec4f::DivEquals(const Vec4f& b)
	{
		this->x /= b.x;
		this->y /= b.y;
		this->z /= b.z;
		this->w /= b.w;
	}

	Vec4f Vec4f::operator/(const Vec4f& b)
	{
		return this->Div(b);
	}

	void Vec4f::operator/=(const Vec4f& b)
	{
		this->DivEquals(b);
	}

	/* Scalar Div Functions */
	Vec4f Vec4f::Div(float b)
	{
		Vec4f vec(this->x / b, this->y / b, this->z / b, this->w / b);
		return vec;
	}

	void Vec4f::DivEquals(float b)
	{
		this->x /= b;
		this->y /= b;
		this->z /= b;
		this->w /= b;
	}

	Vec4f Vec4f::operator/(float b)
	{
		return this->Div(b);
	}

	void Vec4f::operator/=(float b)
	{
		this->DivEquals(b);
	}

	/* Misc */
	std::string Vec4f::to_string()
	{
		return "["+std::to_string(this->x)+", "+std::to_string(this->y)+", "+std::to_string(this->z)+", "+std::to_string(this->w)+:"]";
	}
}
