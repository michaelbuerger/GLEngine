#include "GLEngine/math/Mat4f.hpp"
#include <iostream>

// TODO: Add range protection

namespace GLEngine { namespace math {

    float SumOfProductsOfArrayElements(const float arr1[], const float arr2[], uint len)
    {
        float sum = 0;
        for(uint i=0;i<len;i++)
        {
            sum += (arr1[i] * arr2[i]);
        }

        return sum;
    }

    Mat4f::Mat4f()
    {
        for(uint r=0; r < 4; r++)
        {
            for(uint c=0; c < 4; c++)
            {
                this->matrix[r][c] = 0;
            }
        }
    }
    Mat4f::Mat4f(const float& value)
    {
        for(uint r=0; r < 4; r++)
        {
            for(uint c=0; c < 4; c++)
            {
                this->matrix[r][c] = value;
            }
        }
    }
    Mat4f::Mat4f(const Mat4f& mat1)
    {
        for(uint r=0; r < 4; r++)
        {
            mat1.GetRow(r, this->matrix[r]);
        }
    }
    Mat4f::Mat4f(const float matrix[4][4])
    {
        this->SetRawMatrix(matrix);
    }
    Mat4f::Mat4f(const float values[16])
    {
        this->SetRawMatrix(values);
    }

    float Mat4f::GetElement(const int& row, const int& column) const
    {
        return this->matrix[row][column];
    }

    void Mat4f::SetElement(const int& row, const int& column, const float& value)
    {
        this->matrix[row][column] = value;
    }

    void Mat4f::GetRow(const int& row, float rowValues[4]) const // return by reference
    {
        rowValues[0] = this->matrix[row][0];
        rowValues[1] = this->matrix[row][1];
        rowValues[2] = this->matrix[row][2];
        rowValues[3] = this->matrix[row][3];
    }
    void Mat4f::GetColumn(const int& column, float columnValues[4]) const // return by reference
    {
        columnValues[0] = this->matrix[0][column];
        columnValues[1] = this->matrix[1][column];
        columnValues[2] = this->matrix[2][column];
        columnValues[3] = this->matrix[3][column];
    }

    void Mat4f::SetRow(const int& row, const float rowValues[4])
    {
        this->matrix[row][0] = rowValues[0];
        this->matrix[row][1] = rowValues[1];
        this->matrix[row][2] = rowValues[2];
        this->matrix[row][3] = rowValues[3];
    }
    void Mat4f::SetColumn(const int& column, const float columnValues[4])
    {
         this->matrix[0][column] = columnValues[0];
         this->matrix[1][column] = columnValues[1];
         this->matrix[2][column] = columnValues[2];
         this->matrix[3][column] = columnValues[3];
    }

    void Mat4f::GetRawMatrix(float matrix[4][4]) const // Return by reference
    {
        float row0[4], row1[4], row2[4], row3[4];

        this->GetRow(0, row0);
        this->GetRow(1, row1);
        this->GetRow(2, row2);
        this->GetRow(3, row3);

        *matrix[0] = *row0;
        *matrix[1] = *row1;
        *matrix[2] = *row2;
        *matrix[3] = *row3;
    }
    void Mat4f::SetRawMatrix(const float matrix[4][4])
    {
        this->SetRow(0, matrix[0]);
        this->SetRow(1, matrix[1]);
        this->SetRow(2, matrix[2]);
        this->SetRow(3, matrix[3]);
    }
    void Mat4f::SetRawMatrix(const float values[16]) // Top left to bottom right
    {
        uint i = 0;

        for(uint r=0; r < 4; r++)
        {
            for(uint c=0; c < 4; c++)
            {
                this->matrix[r][c] = values[i];
                i++;
            }
        }
    }

    Mat4f Mat4f::mult(const Mat4f& mat2)
    {
        float finalValues[16];
        int i = 0;

        for(uint mat1_r=0; mat1_r < 4; mat1_r++)
        {
            for(uint mat2_c=0; mat2_c < 4; mat2_c++)
            {
                float mat1_row[4] = { 0, 0, 0, 0 };
                float mat2_column[4] = { 0, 0, 0, 0 };

                this->GetRow(mat1_r, mat1_row);
                mat2.GetColumn(mat2_c, mat2_column);

                finalValues[i] = SumOfProductsOfArrayElements(mat1_row, mat2_column, 4);
                i++;
            }
        }

        this->SetRawMatrix(finalValues);

        return *this;
    }
    Mat4f Mat4f::Mult(const Mat4f& mat1, const Mat4f& mat2)
    {
        Mat4f finalMat(mat1);

        finalMat.mult(mat2);  

        return finalMat;
    }
    Mat4f Mat4f::mult(const float& scalar)
    {
        for(uint r=0; r < 4; r++)
        {
            for(uint c=0; c < 4; c++)
            {
                this->matrix[r][c] *= scalar;
            }
        }

        return *this;
    }
    Mat4f Mat4f::Mult(const Mat4f& mat1, const float& scalar)
    {
        Mat4f finalMat(mat1);

        finalMat.mult(scalar);

        return finalMat;
    }

    Mat4f Mat4f::add(const Mat4f& mat2)
    {
        for(uint r=0; r < 4; r++)
        {
            for(uint c=0; c < 4; c++)
            {
                this->matrix[r][c] += mat2.GetElement(r, c);
            }
        }

        return *this;
    }
    Mat4f Mat4f::Add(const Mat4f& mat1, const Mat4f& mat2)
    {
        Mat4f finalMat(mat1);

        finalMat.add(mat2);

        return finalMat;
    }

}}