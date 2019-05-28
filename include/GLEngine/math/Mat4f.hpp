#ifndef MAT4F_HPP
#define MAT4F_HPP

#include <iostream>

inline std::ostream& operator<<(std::ostream& os, float val[4])
{
    os << "{";
    for(uint i=0; i<4; i++)
    {
        if(i<3)
        {
            os << val[i] << ", ";
        } else 
        {
            os << val[i];
        }
    }
    os << "}";

    return os;
}

namespace GLEngine { namespace math {

    class Mat4f 
    {
        public:
            Mat4f();
            Mat4f(const float& value);
            Mat4f(const Mat4f& mat1);
            Mat4f(const float matrix[4][4]);
            Mat4f(const float values[16]);

            float GetElement(const int& row, const int& column) const;

            void SetElement(const int& row, const int& column, const float& value);

            void GetRow(const int& row, float rowValues[4]) const; // return by reference
            void GetColumn(const int& column, float columnValues[4]) const; // return by reference

            void SetRow(const int& row, const float rowValues[4]);
            void SetColumn(const int& column, const float columnValues[4]);

            void GetRawMatrix(float matrix[4][4]) const; // Return by reference

            void SetRawMatrix(const float matrix[4][4]);
            void SetRawMatrix(const float values[16]); // Top left to bottom right

            Mat4f mult(const Mat4f& mat2);
            static Mat4f Mult(const Mat4f& mat1, const Mat4f& mat2);
            Mat4f mult(const float& scalar);
            static Mat4f Mult(const Mat4f& mat1, const float& scalar);

            Mat4f add(const Mat4f& mat2);
            static Mat4f Add(const Mat4f& mat1, const Mat4f& mat2);

        private:
            float matrix[4][4]; // rows by columns (y by x)
    };

    inline std::ostream& operator<<(std::ostream& os, const Mat4f& mat) /* Converts Mat4f to output stream (cout-able) */
    {
        for(int y = 0; y < 4; y++)
        {
            os << "[";
            for(int x = 0; x < 4; x++)
            {
                if(x < 3)
                {
                    os << mat.GetElement(y, x) << ", ";
                } else
                {
                    os << mat.GetElement(y, x);
                }
            }
            os << "]" << std::endl;
        }

        return os;
    }

}}

#endif