#pragma once

#include "Actor.h"

class CAnimSpriteComponent;

class AAnimSpriteActor : public AActor
{
public:

	AAnimSpriteActor();

	CAnimSpriteComponent* GetAnimSpriteComponent() const { return mAnimSpriteComponent; }

	Vector2D GetActorSize() const override;

protected:
	CAnimSpriteComponent* mAnimSpriteComponent;

};