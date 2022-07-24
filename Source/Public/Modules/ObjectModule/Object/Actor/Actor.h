#pragma once

#include "Modules/ObjectModule/Object.h"
#include "Modules/MathModule/Vector2D.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

#include <algorithm>

class CTransform2DComponent;
class CBaseComponent;

class AActor : public OObject
{

public:
	AActor();

	AActor(const AActor& actor)		= default;
	AActor(AActor&& actor)			= default;

	AActor &operator=(const AActor& actor)	= default;
	AActor &operator=(AActor&& actor)		= default;

	virtual void					BeginPlay() override;

    virtual void					Tick(float deltaTime) override;

	CTransform2DComponent*			GetRootComponent() const { return RootComponent; }
	void							SetRootComponent(CTransform2DComponent *NewRoot);

	Vector2D						GetActorPosition() const { return RootComponent->GetRelativePosition(); }
	float							GetActorRotationAngle() const { return RootComponent->GetRelativeRotationAngle(); }
	Vector2D						GetActorScale() const { return RootComponent->GetRelativeScale(); }

	virtual Vector2D				GetActorSize() const { return GetActorScale(); }

	void							SetActorPosition(Vector2D InPosition);
	void							SetActorRotationAngle(float InRotationAngle);
	void							SetActorScale(Vector2D InScale);

	bool							GetIsPendingToKill() const { return mIsPendingToKill; }
	void							SetIsPendingToKill(bool newIsPendingToKill);

	vector<CBaseComponent*>			GetComponents() const { return mComponents; }	

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

	void							RemoveComponent(CBaseComponent* Component);

	virtual void					Destroy() override;

	~AActor();

protected:
	vector<CBaseComponent*>	mComponents;
	bool							mIsPendingToKill = false;
private:
	CTransform2DComponent			*RootComponent;

};