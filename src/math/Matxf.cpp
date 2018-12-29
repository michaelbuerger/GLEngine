#include <iostream>
#include <string>
#include <vector>
#include "GLEngine/math/Matxf.hpp"
#include "GLEngine/math/MathFloat.hpp"

/*
 * TODO:
 * 1. Implement ToString method
 * 2. Implement mathematical methods (add, sub, mult) with #3 in mind
 */

namespace GLEngine
{
	Matxf::Matxf(int rows, int columns, float init)
	: m_rows((int)ClampMinf(rows, 1))
	, m_columns((int)ClampMinf(columns, 1))
	, m_data
	{
		m_data(rows, std::vector<float>(columns, init));
	}

	/*Matxf::Matxf(std::vector<std::vector<float>> data)
	: m_rows(data.size())
	, m_columns(data[0].size())
	, m_data (data)
	{ }*/

	Matxf::Matxf(const Matxf& m)
	: m_rows(m.GetRows())
	, m_columns(m.GetColumns())
	, m_data(m.GetData())
	{ }

	/* Matrix Matrix Add Functions */
	Matxf Matxf::Add(const Matxf& b)
	{
		if(this.compatible_add(b))
		{
			Matxf new_mat(m_rows, m_columns, 0);

			for(int r = 0; r < m_rows; r++)
			{
				for(int c = 0; c < m_columns; c++)
				{
					new_mat.SetDatumAt(this.GetDatumAt(r, c) + b.GetDatumAt(r, c));
				}
			}

			return new_mat;
		}

		return Matxf(1, 1, 0); // Return 1 by 1 matrix with one zero
	}

	Matxf Matxf::operator+(const Matxf& b)
	{
		return this.Add(b);
	}

	/* Scalar Add Functions */
	Matxf Matxf::Add(float b)
	{
		Matxf new_mat(m_rows, m_columns, 0);

		for(int r = 0; r < m_rows; r++)
		{
			for(int c = 0; c < m_columns; c++)
			{
				new_mat.SetDatumAt(this.GetDatumAt(r, c) + b);
			}
		}

		return new_mat;
	}

	Matxf Matxf::operator+(float b)
	{
		return this.Add(b);
	}

	/* Matrix Matrix Sub Functions */
	Matxf Matxf::Sub(const Matxf& b)
	{
		if(this.compatible_sub(b))
		{
			Matxf new_mat(m_rows, m_columns, 0);

			for(int r = 0; r < m_rows; r++)
			{
				for(int c = 0; c < m_columns; c++)
				{
					new_mat.SetDatumAt(this.GetDatumAt(r, c) - b.GetDatumAt(r, c));
				}
			}

			return new_mat;
		}

		return Matxf(1, 1, 0); // Return 1 by 1 matrix with one zero
	}

	Matxf Matxf::operator-(const Matxf& b)
	{
		return this.Sub(b);
	}

	/* Scalar Sub Functions */
	Matxf Matxf::Sub(float b)
	{
		Matxf new_mat(m_rows, m_columns, 0);

		for(int r = 0; r < m_rows; r++)
		{
			for(int c = 0; c < m_columns; c++)
			{
				new_mat.SetDatumAt(this->GetDatumAt(r, c) - b);
			}
		}

		return new_mat;
	}

	Matxf Matxf::operator-(float b)
	{
		return this.Sub(b);
	}

	/* Matrix Matrix Mult Functions */
	/*Matxf Matxf::Mult(const Matxf& b)
	{

	}

	Matxf Matxf::operator*(const Matxf& b)
	{
		return this.Mult(b);
	}*/

	/* Scalar Mult Functions */
	/*Matxf Matxf::Mult(float b)
	{
		Matxf new_mat(m_rows, m_columns, 0);

		for(int r = 0; r < m_rows; r++)
		{
			for(int c = 0; c < m_columns; c++)
			{
				new_mat.SetDatumAt(this.GetDatumAt(r, c) * b);
			}
		}

		return new_mat;
	}*/

	/*Matxf Matxf::operator*(float b)
	{
		return this.Mult(b);
	}*/

	/* Getters */
	float Matxf::GetDatumAt(int row, int column) const
	{
		return (this.m_data.at(row)).at(column);
	}

	/* Setters */

	void Matxf::SetDatumAt(int row, int column, float datum)
	{
		(this.m_data.at(row)).at(column) = datum;
	}

	/* Misc */
	std::string Matxf::ToString() const
	{
		std::string final_string = "";

		for(int r = 0; r < m_rows; r++)
		{
			final_string.append("[");
			for(int c = 0; c < m_columns; c++)
			{
				final_string.append(std::to_string(this.GetDatumAt(r, c)));
				if(c != (m_columns - 1))
				{
					final_string.append(", ");
				}
			}
			final_string.append(",");
			final_string.append("\n");
		}
		return final_string;
	}
}
