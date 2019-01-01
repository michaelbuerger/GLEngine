#ifndef MATHFLOAT_HPP
#define MATHFLOAT_HPP

namespace GLEngine { namespace math
{
	/* Clamp [num] between [min] and [max] */
	float Clampf(float num, float min, float max)
	{
		float num_final = num;

		if (num < min)
		{
			num_final = min;
		} else if(num > max)
		{
			num_final = max;
		}

		return num_final;
	}

	/* Clamp [num] between [min] and INFINITY */
	float ClampMinf(float num, float min)
	{
		float num_final = num;

		if(num < min)
		{
			num_final = min;
		}

		return num_final;
	}

	/* Clamp [num] between NEG_INFINITY and [max] */
	float ClampMaxf(float num, float max)
	{
		float num_final = num;

		if (num > max)
		{
			num_final = max;
		}

		return num_final;
	}
}}
#endif /* end of include guard:MATHFLOAT_HPP */
