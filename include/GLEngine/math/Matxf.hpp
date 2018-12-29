#ifndef MATXF_HPP
#define MATXF_HPP

#include <iostream>
#include <string>
#include <vector>

namespace GLEngine
{
	class Matxf
	{
	private:
		int m_rows, m_columns;
		std::vector<std::vector<float>> m_data;

	public:
		Matxf(int rows, int columns, float init);

		/* TODO: Auto-format matrices formed by the following constructor if necessary */
		// Matxf(std::vector<std::vector<float>> data);

		Matxf(const Matxf& m);

		/* Matrix Matrix Add Functions */
		Matxf Add(const Matxf& b);
		Matxf operator+(const Matxf& b);
		/* Scalar Add Functions */
		Matxf Add(float b);
		Matxf operator+(float b);

		/* Matrix Matrix Sub Functions */
		Matxf Sub(const Matxf& b);
		Matxf operator-(const Matxf& b);
		/* Scalar Sub Functions */
		Matxf Sub(float b);
		Matxf operator-(float b);

		/* Matrix Matrix Mult Functions */
		//Matxf Mult(const Matxf& b);
		//Matxf operator*(const Matxf& b);
		/* Scalar Mult Functions */
		//Matxf Mult(float b);
		//Matxf operator*(float b);

		/* Tests for mathematical viability */
		inline bool compatible_add(const Matxf& b) const { return (m_rows == b.GetRows()) && (m_columns == b.GetColumns()); };
		inline bool compatible_sub(const Matxf& b) const { return (m_rows == b.GetRows()) && (m_columns == b.GetColumns()); };
		inline bool compatible_mult(const Matxf& b) const { return m_columns == b.GetRows(); };
		inline static bool compatible_add(const Matxf& a, const Matxf& b) { return a.compatible_add(b); };
		inline static bool compatible_sub(const Matxf& a, const Matxf& b) { return a.compatible_sub(b); };
		inline static bool compatible_mult(const Matxf& a, const Matxf& b) { return a.compatible_mult(b); };

		/* Getters */
		inline float GetRows() const { return m_rows; };
		inline float GetColumns() const { return m_columns; };
		inline std::vector<std::vector<float>> GetData() const { return m_data; };
		float GetDatumAt(int row, int column) const;

		/* Setters */
		void SetDatumAt(int row, int column, float datum);

		/* Misc */
		std::string ToString() const;
	};
}

#endif /* end of include guard MATXF_HPP */
