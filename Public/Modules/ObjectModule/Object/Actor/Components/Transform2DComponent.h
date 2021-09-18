#pragma once

#include "Modules/MathModule/Vector2D.h"
#include "Modules/MathModule/Matrix4.h"

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class CTransform2DComponent : public CBaseComponent
{

public:

	void		SetPosition(const Vector2D& newPosition);
	void		SetScale(const Vector2D& newScale);
	void		SetAngle(float newRotationAngle);

	Vector2D	GetPosition() const { return mPosition; }
	Vector2D	GetScale() const { return mScale; }
	float		GetAngle() const { return mRotationAngle; }

	virtual void BeginPlay() override;

	Matrix4D	GetComputedTransform() const;

private:

	void		ComputeTransform();

	Matrix4D	mComputedTransform;

	Matrix4D	mTransfromPosition;
	Matrix4D	mTransfromRotation;
	Matrix4D	mTransfromScale;

	Vector2D	mPosition;
	Vector2D	mScale = Vector2D::UnitVector;
	float		mRotationAngle = 0;
};