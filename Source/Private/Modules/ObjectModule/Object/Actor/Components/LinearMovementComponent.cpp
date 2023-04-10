
#include "Modules/ObjectModule/Object/Actor/Components/LinearMovementComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include <algorithm>

void CLinearMovementComponent::Tick(float deltaTime)
{
	Movement(deltaTime);
}

void CLinearMovementComponent::Movement(float deltaTime)
{
	GetOwner()->SetActorPosition(GetOwner()->GetActorPosition() + Vector2D(mVelocity * mSpeed * deltaTime));
}

void CLinearMovementComponent::SetSpeed(float newSpeed)
{
	mSpeed = std::clamp(newSpeed, 100.f, 1000.f);
}

void CLinearMovementComponent::SetVelocity(Vector2D newVelocity)
{
	mVelocity = newVelocity;

	mVelocity.X() = std::clamp(mVelocity.X(), -1.f, 1.f);
	mVelocity.Y() = std::clamp(mVelocity.Y(), -1.f, 1.f);
}