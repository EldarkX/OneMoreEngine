#pragma once

class Vector2D
{

public:
					Vector2D();
					
					Vector2D(float x, float y);
					
					Vector2D(const Vector2D& Vector) = default;
					
					Vector2D(Vector2D && Vector) = default;

	Vector2D		operator=(const Vector2D& Vector);

	Vector2D &		operator+=(const Vector2D& Vector);
	Vector2D &		operator-=(const Vector2D& Vector);
	Vector2D &		operator*=(const Vector2D& Vector);
	Vector2D &		operator/=(const Vector2D& Vector);

    float			Size() const;

	inline float&	X() { return data_[0]; }
	inline float	X() const { return data_[0]; }

	inline float&	Y() { return data_[1]; }
	inline float	Y() const { return data_[1]; }

	/*static*/
	static const	Vector2D UnitVector;
	static const	Vector2D ZeroVector;

protected:

	float			data_[2];

};

inline Vector2D operator/(const Vector2D& v, float scalar)
{
	float reversedScalar = 1 / scalar;
	return (Vector2D(v.X() * reversedScalar, v.Y() * reversedScalar));
}

inline Vector2D operator*(const Vector2D &v, float scalar) { return (Vector2D(v.X() * scalar, v.Y() * scalar)); }
inline Vector2D operator*(const Vector2D &v1, const Vector2D& v2) { return (Vector2D(v1.X() * v2.X(), v1.Y() * v2.Y())); }
inline Vector2D operator+(const Vector2D& v1, const Vector2D& v2) { return (Vector2D(v1.X() + v2.X(), v1.Y() + v2.Y())); }
inline Vector2D operator-(const Vector2D& v1, const Vector2D& v2) { return (Vector2D(v1.X() - v2.X(), v1.Y() - v2.Y())); }
inline Vector2D operator-(const Vector2D& Vector) { return Vector2D(-Vector.X(), -Vector.Y()); }
Vector2D Normalize(const Vector2D& Vector);
