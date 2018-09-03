#pragma once

#include <iostream>
#include <string>

namespace GLEngine
{
	class Vec4f
	{
	public:
		float x, y, z, w;

		Vec4f();
		Vec4f(float x, float y, float z, float w);
		Vec4f(const Vec4f& v);

		float Magnitude();

		/* Vector Vector Add Functions */
		Vec4f Add(const Vec4f& b);
		void AddEquals(const Vec4f& b);
		Vec4f operator+(const Vec4f& b);
		void operator+=(const Vec4f& b);
		/* Scalar Add Functions */
		Vec4f Add(float b);
		void AddEquals(float b);
		Vec4f operator+(float b);
		void operator+=(float b);

		/* Vector Vector Sub Functions */
		Vec4f Sub(const Vec4f& b);
		void SubEquals(const Vec4f& b);
		Vec4f operator-(const Vec4f& b);
		void operator-=(const Vec4f& b);
		/* Scalar Sub Functions */
		Vec4f Sub(float b);
		void SubEquals(float b);
		Vec4f operator-(float b);
		void operator-=(float b);

		/* Vector Vector Mult Functions */
		Vec4f Mult(const Vec4f& b);
		void MultEquals(const Vec4f& b);
		Vec4f operator*(const Vec4f& b);
		void operator*=(const Vec4f& b);
		/* Scalar Mult Functions */
		Vec4f Mult(float b);
		void MultEquals(float b);
		Vec4f operator*(float b);
		void operator*=(float b);

		/* Vector Vector Div Functions */
		Vec4f Div(const Vec4f& b);
		void DivEquals(const Vec4f& b);
		Vec4f operator/(const Vec4f& b);
		void operator/=(const Vec4f& b);
		/* Scalar Div Functions */
		Vec4f Div(float b);
		void DivEquals(float b);
		Vec4f operator/(float b);
		void operator/=(float b);

		/* Misc */
		std::string to_string();
	};
}
