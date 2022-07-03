
#include "Modules/MathModule/Vector2D.h"

#include <cmath>

const Vector2D Vector2D::UnitVector(1.f, 1.f);
const Vector2D Vector2D::ZeroVector(0.f, 0.f);

Vector2D::Vector2D()
{
	data_[0] = 0;
	data_[1] = 0;
};

Vector2D::Vector2D(float x, float y)
{
	data_[0] = x;
	data_[1] = y;
};

Vector2D& Vector2D::operator+=(const Vector2D& Vector)
{
	data_[0] += Vector.X();
	data_[1] += Vector.Y();

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& Vector)
{
	data_[0] -= Vector.X();
	data_[1] -= Vector.Y();

	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& Vector)
{
	data_[0] *= Vector.X();
	data_[1] *= Vector.Y();

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& Vector)
{
	data_[0] /= Vector.X();
	data_[1] /= Vector.Y();

	return *this;
}

Vector2D Vector2D::operator=(const Vector2D& Vector)
{
	data_[0] = Vector.X();
	data_[1] = Vector.Y();

	return *this;
}

float Vector2D::Size() const
{
    return (static_cast<float>(sqrt(pow(data_[0], 2) + pow(data_[1], 2))));
}

Vector2D Normalize(const Vector2D& Vector)
{
	float VectorSize = Vector.Size();
	return !VectorSize ? Vector2D::ZeroVector : Vector / VectorSize;
}
