#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"
#include <algorithm>

void CTransform2DComponent::BeginPlay()
{
	CBaseComponent::BeginPlay();

	ComputedWorldPosition = Matrix4D::OneMatrix();
	ComputedWorldRotation = Matrix4D::OneMatrix();
	ComputedWorldScale = Matrix4D::OneMatrix();

	ComputedWorldPosition(2, 2) = 0;

	ComputeTransform();
}

void CTransform2DComponent::SetRelativePosition(const Vector2D &InPosition)
{
	RelativePosition = InPosition;
	ComputeTransform();

	if (ChildComponent)
	{
		ChildComponent->ComputeTransform();
	}
}

void CTransform2DComponent::SetRelativeRotationAngle(float InRotationAngle)
{
	RelativeRotationAngle = InRotationAngle;
	ComputeTransform();

	if (ChildComponent)
	{
		ChildComponent->ComputeTransform();
	}
}

void CTransform2DComponent::SetRelativeScale(const Vector2D& InScale)
{
	RelativeScale = RelativeScale;
	ComputeTransform();

	if (ChildComponent)
	{
		ChildComponent->ComputeTransform();
	}
}

void CTransform2DComponent::ComputeTransform()
{
	Vector2D	WorldPosition = GetWorldPosition();
	float		WorldRotationAngle = GetWorldRotationAngle();
	Vector2D	WorldScale = GetWorldScale();

	ComputedWorldPosition(3, 0) = WorldPosition.X();
	ComputedWorldPosition(3, 1) = WorldPosition.Y();

	const float RotRad = (WorldRotationAngle * 3.1415f) / 180.f;

	float cosA = cos(RotRad);
	float sinA = sin(RotRad);

	ComputedWorldRotation(0, 0) = cosA;
	ComputedWorldRotation(0, 1) = sinA;
	ComputedWorldRotation(1, 0) = -sinA;
	ComputedWorldRotation(1, 1) = cosA;

	ComputedWorldScale(0, 0) = WorldScale.X();
	ComputedWorldScale(1, 1) = WorldScale.Y();

	ComponentToWorldTransform = ComputedWorldScale;
	ComponentToWorldTransform = ComponentToWorldTransform * ComputedWorldRotation;
	ComponentToWorldTransform = ComponentToWorldTransform * ComputedWorldPosition;
}

Matrix4D CTransform2DComponent::GetComputedWorldTransform() const
{
	return ComponentToWorldTransform;
}

void CTransform2DComponent::AttachToComponent(CTransform2DComponent* InParent)
{
	AttachedParent = InParent;
	InParent->SetChildComponent(this);
}

CTransform2DComponent* CTransform2DComponent::GetChildComponent() const
{
	return ChildComponent;
}

void CTransform2DComponent::SetChildComponent(CTransform2DComponent* InChild)
{
	ChildComponent = InChild;
}	

Vector2D CTransform2DComponent::GetWorldPosition() const
{
	return RelativePosition + (AttachedParent ? AttachedParent->GetWorldPosition() : Vector2D::ZeroVector);
}

Vector2D CTransform2DComponent::GetWorldScale() const
{
	if (AttachedParent)
	{
		return RelativeScale * AttachedParent->GetWorldScale();
	}
	return RelativeScale;
}

float CTransform2DComponent::GetWorldRotationAngle()
{
	return RelativeRotationAngle + (AttachedParent ? AttachedParent->GetWorldRotationAngle() : 0.f);
}
