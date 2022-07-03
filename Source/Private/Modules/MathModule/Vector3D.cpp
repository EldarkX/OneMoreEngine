#include "Modules/MathModule/Vector3D.h"

#include <cmath>

Vector3D::Vector3D()
{
	data_[0] = 0;
	data_[1] = 0;
	data_[2] = 0;
};

Vector3D::Vector3D(float x, float y, float z)
{
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
};

float Vector3D::Size() const 
{
	return (sqrt(pow(data_[0], 2) + pow(data_[1], 2) + pow(data_[2], 2)));
}
