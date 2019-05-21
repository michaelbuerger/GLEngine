#ifndef MATHFLOAT_HPP
#define MATHFLOAT_HPP

namespace GLEngine { namespace math
{
	/* Clamp [num] between [min] and [max] */
	float Clampf(float num, float min, float max);

	/* Clamp [num] between [min] and INFINITY */
	float ClampMinf(float num, float min);

	/* Clamp [num] between NEG_INFINITY and [max] */
	float ClampMaxf(float num, float max);
}}
#endif
