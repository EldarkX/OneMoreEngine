
#include "Modules/MathModule/Matrix4.h"

Matrix4D::Matrix4D(vector<vector<float>> Values)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			mData[i][j] = Values[i][j];
	}
}

Matrix4D Matrix4D::OneMatrix()
{
	return (Matrix4D({
			{1.f, 0.f, 0.f, 0.f},
			{0.f, 1.f, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 0.f, 1.f},
		})
	);
}

Matrix4D Matrix4D::ZeroMatrix()
{
	return (Matrix4D({
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
		})
	);
}

Matrix4D operator*(const Matrix4D& m, float scalar)
{
	Matrix4D result = m;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			result(i, j) *= scalar;
	}
	return result;
}

//Matrix4D operator*=(const Matrix4D& m)
//{
//	Matrix4D result = (*this * m);
//	return result;
//}

Matrix4D operator+(const Matrix4D& m1, const Matrix4D& m2)
{
	Matrix4D result;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			result(i, j) = m1(i, j) + m2(i, j);
	}
	return result;
}

Matrix4D operator-(const Matrix4D& m1, const Matrix4D& m2)
{
	Matrix4D result;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			result(i, j) = m1(i, j) - m2(i, j);
	}
	return result;
}

Matrix4D operator-(const Matrix4D& m)
{
	Matrix4D result = m;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			result(i, j) *= -1;
	}
	return result;
}