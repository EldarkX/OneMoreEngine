#pragma once

#include "Modules/ObjectModule/Object/Actor/Actor.h"

class CSpriteComponent;

class ASpriteActor : public AActor
{
public:
	ASpriteActor();

	CSpriteComponent* GetSpriteComponent() const { return mSpriteComponent; }

	Vector2D GetActorSize() const override;

protected:
	CSpriteComponent* mSpriteComponent;
};
