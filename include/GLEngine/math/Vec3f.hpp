#pragma once

#include <iostream>
#include <string>

namespace GLEngine
{
	class Vec3f
	{
	public:
		float x, y, z;

		Vec3f();
		Vec3f(float x, float y, float z);
		Vec3f(const Vec3f& v);

		float Magnitude();

		/* Vector Vector Add Functions */
		Vec3f Add(const Vec3f& b);
		void AddEquals(const Vec3f& b);
		Vec3f operator+(const Vec3f& b);
		void operator+=(const Vec3f& b);
		/* Scalar Add Functions */
		Vec3f Add(float b);
		void AddEquals(float b);
		Vec3f operator+(float b);
		void operator+=(float b);

		/* Vector Vector Sub Functions */
		Vec3f Sub(const Vec3f& b);
		void SubEquals(const Vec3f& b);
		Vec3f operator-(const Vec3f& b);
		void operator-=(const Vec3f& b);
		/* Scalar Sub Functions */
		Vec3f Sub(float b);
		void SubEquals(float b);
		Vec3f operator-(float b);
		void operator-=(float b);

		/* Vector Vector Mult Functions */
		Vec3f Mult(const Vec3f& b);
		void MultEquals(const Vec3f& b);
		Vec3f operator*(const Vec3f& b);
		void operator*=(const Vec3f& b);
		/* Scalar Mult Functions */
		Vec3f Mult(float b);
		void MultEquals(float b);
		Vec3f operator*(float b);
		void operator*=(float b);

		/* Vector Vector Div Functions */
		Vec3f Div(const Vec3f& b);
		void DivEquals(const Vec3f& b);
		Vec3f operator/(const Vec3f& b);
		void operator/=(const Vec3f& b);
		/* Scalar Div Functions */
		Vec3f Div(float b);
		void DivEquals(float b);
		Vec3f operator/(float b);
		void operator/=(float b);

		/* Misc */
		std::string to_string();
	};
}
