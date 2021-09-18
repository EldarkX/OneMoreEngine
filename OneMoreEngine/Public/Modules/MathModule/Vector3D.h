#pragma once

class Vector3D
{

public:

					Vector3D();
					
					Vector3D(float x, float y, float z);
				
					Vector3D(const Vector3D& Vector) = default;
				
					Vector3D(Vector3D&& Vector) = default;

	inline float&	X()			{ return data_[0]; }
	inline float	X() const	{ return data_[0]; }

	inline float&	Y()			{ return data_[1]; }
	inline float	Y() const	{ return data_[1]; }

	inline float&	Z()			{ return data_[2]; }
	inline float	Z() const	{ return data_[2]; }
	
	float			Size() const;

private:

	float			data_[3];

};

