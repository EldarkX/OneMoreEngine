#pragma once

#include <vector>

using std::vector;

class Matrix4D
{

public:

	Matrix4D() = default;

	Matrix4D(const Matrix4D& matrix) = default;

	Matrix4D(Matrix4D&& matrix) = default;

	Matrix4D& operator=(const Matrix4D& matrix) = default;

	Matrix4D(vector<vector<float>> Values);

	float &operator()(int row, int col) { return mData[row][col]; }
	float operator()(int row, int col) const { return mData[row][col]; }

	//inline Matrix4D& operator*=(const Matrix4D& m);

	static Matrix4D OneMatrix();
	static Matrix4D ZeroMatrix();

private:

	float mData[4][4];
};

inline Matrix4D operator*(const Matrix4D& m, float scalar);
inline Matrix4D operator*(const Matrix4D& m1, const Matrix4D& m2)
{
	Matrix4D result;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float num = 0;
			for (int k = 0; k < 4; ++k)
			{
				num += m1(i, k) * m2(k, j);
			}
			result(i, j) = num;
		}
	}
	return result;
}

inline Matrix4D operator+(const Matrix4D& m1, const Matrix4D& m2);
inline Matrix4D operator-(const Matrix4D& m1, const Matrix4D& m2);
inline Matrix4D operator-(const Matrix4D& m);