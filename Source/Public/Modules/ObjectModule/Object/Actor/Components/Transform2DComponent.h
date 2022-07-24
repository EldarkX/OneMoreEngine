#pragma once

#include "Modules/MathModule/Vector2D.h"
#include "Modules/MathModule/Matrix4.h"

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class CTransform2DComponent : public CBaseComponent
{

public:
	virtual void			BeginPlay() override;

	void					SetRelativePosition(const Vector2D& InPosition);
	void					SetRelativeRotationAngle(float InRotationAngle);
	void					SetRelativeScale(const Vector2D& InScale);

	Vector2D				GetRelativePosition() const { return RelativePosition; }
	Vector2D				GetRelativeScale() const { return RelativeScale; }
	float					GetRelativeRotationAngle() const { return RelativeRotationAngle; }

	Vector2D				GetWorldPosition() const;
	Vector2D				GetWorldScale() const;
	float					GetWorldRotationAngle();

	Matrix4D				GetComputedWorldTransform() const;

	void					AttachToComponent(CTransform2DComponent* InParent);
	CTransform2DComponent*	GetChildComponent() const;
protected:
	void					SetChildComponent(CTransform2DComponent* InChild);

	CTransform2DComponent*	AttachedParent = nullptr;
	CTransform2DComponent*	ChildComponent = nullptr;

private:
	void					ComputeTransform();

	Matrix4D				ComponentToWorldTransform;

	Matrix4D				ComputedWorldPosition;
	Matrix4D				ComputedWorldRotation;
	Matrix4D				ComputedWorldScale;

	Vector2D				RelativePosition = Vector2D::ZeroVector;
	Vector2D				RelativeScale = Vector2D::UnitVector;
	float					RelativeRotationAngle = 0.f;
};