#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class CLinearMovementComponent : public CBaseComponent
{

public:

	virtual void					Tick(float deltaTime) override;

	virtual void					Movement(float deltaTime);

	float							GetSpeed() const { return mSpeed; }
	void							SetSpeed(float newSpeed);

	inline Vector2D					GetVelocity() const { return mVelocity; }
	void							SetVelocity(Vector2D newVelocity);

private:

	float							mSpeed = 0;
	Vector2D						mVelocity = Vector2D::ZeroVector;

};

