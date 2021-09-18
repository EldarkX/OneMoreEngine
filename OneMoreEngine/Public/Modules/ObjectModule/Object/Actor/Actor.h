#pragma once

#include "Modules/ObjectModule/Object.h"
#include "Modules/MathModule/Vector2D.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

#include <algorithm>

class AActor : public OObject
{

public:

	AActor();

	virtual void					BeginPlay() override;

    virtual void					Tick(float deltaTime) override;

	class CTransform2DComponent		*GetActorTransform() const { return mTransformComponent; }

	Vector2D						GetActorPosition() const { return mTransformComponent->GetPosition(); }
	Vector2D						GetActorScale() const { return mTransformComponent->GetScale(); }

	virtual Vector2D				GetActorSize() const { return GetActorScale(); }

	void							SetActorPosition(Vector2D newPosition) { mTransformComponent->SetPosition(newPosition); }
	void							SetActorScale(Vector2D newScale) { mTransformComponent->SetScale(newScale); }

	bool							GetIsPendingToKill() const { return mIsPendingToKill; }
	void							SetIsPendingToKill(bool newIsPendingToKill);

	vector<class CBaseComponent*>	GetComponents() const { return mComponents; }

	MulticastDelegate1<AActor*>		OnStartBeingPendingToKill;

	template<class T>
	T* AddComponent()
	{
		CBaseComponent* NewComponent = new T();

		NewComponent->SetOwner(this);

		NewComponent->BeginPlay();

		mComponents.push_back(NewComponent);

		return dynamic_cast<T *>(NewComponent);
	}

	void							RemoveComponent(class CBaseComponent* Component);

	virtual void					Destroy() override;

	~AActor();

protected:

	vector<class CBaseComponent*>	mComponents;

	class CTransform2DComponent		*mTransformComponent;

	bool			mIsPendingToKill = false;

};