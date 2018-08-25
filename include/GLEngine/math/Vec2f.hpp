#pragma once

#include <iostream>
#include <string>
#include "GLEngine/math/Vec3f-fwd.hpp"

namespace GLEngine
{
	class Vec2f
	{
	public:
		float x, y;

		Vec2f(float x, float y);
		Vec2f(const Vec3f& v);

		float Magnitude();

		/* Vector Vector Add Functions */
		Vec2f Add(const Vec2f& b);
		void AddEquals(const Vec2f& b);
		Vec2f operator+(const Vec2f& b);
		void operator+=(const Vec2f& b);
		/* Scalar Add Functions */
		Vec2f Add(float b);
		void AddEquals(float b);
		Vec2f operator+(float b);
		void operator+=(float b);

		/* Vector Vector Sub Functions */
		Vec2f Sub(const Vec2f& b);
		void SubEquals(const Vec2f& b);
		Vec2f operator-(const Vec2f& b);
		void operator-=(const Vec2f& b);
		/* Scalar Sub Functions */
		Vec2f Sub(float b);
		void SubEquals(float b);
		Vec2f operator-(float b);
		void operator-=(float b);

		/* Vector Vector Mult Functions */
		Vec2f Mult(const Vec2f& b);
		void MultEquals(const Vec2f& b);
		Vec2f operator*(const Vec2f& b);
		void operator*=(const Vec2f& b);
		/* Scalar Mult Functions */
		Vec2f Mult(float b);
		void MultEquals(float b);
		Vec2f operator*(float b);
		void operator*=(float b);

		/* Vector Vector Div Functions */
		Vec2f Div(const Vec2f& b);
		void DivEquals(const Vec2f& b);
		Vec2f operator/(const Vec2f& b);
		void operator/=(const Vec2f& b);
		/* Scalar Div Functions */
		Vec2f Div(float b);
		void DivEquals(float b);
		Vec2f operator/(float b);
		void operator/=(float b);

		/* Misc */
		std::string to_string();
	};
}
