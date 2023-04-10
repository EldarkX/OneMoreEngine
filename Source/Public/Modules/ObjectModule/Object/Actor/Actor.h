#pragma once

#include "Modules/ObjectModule/Object.h"

#include "Modules/MathModule/Vector2D.h"
#include "Modules/ObjectModule/Object/Components/BaseComponent.h"
#include "Utils/Delegate/MulticastDelegate.h"

#include <vector>

class CTransform2DComponent;
class AActor;

class AActor : public OObject
{
public:
	AActor();

	AActor(const AActor& actor)				= default;
	AActor(AActor&& actor)					= default;

	AActor &operator=(const AActor& actor)	= default;
	AActor &operator=(AActor&& actor)		= default;

	virtual void				BeginPlay() override;

    virtual void				Tick(float deltaTime) override;

	CTransform2DComponent*		GetActorTransform() const { return mTransformComponent; }

	Vector2D					GetActorPosition() const;
	Vector2D					GetActorScale() const;

	virtual Vector2D			GetActorSize() const { return GetActorScale(); }

	void						SetActorPosition(Vector2D newPosition);
	void						SetActorScale(Vector2D newScale);

	bool						GetIsPendingToKill() const { return mIsPendingToKill; }
	void						SetIsPendingToKill(bool newIsPendingToKill);

	std::vector<CBaseComponent*>	&GetComponents() { return mComponents; }

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
public:
	DelegateLib::MulticastDelegate1<AActor*>	OnStartBeingPendingToKill;

protected:
	std::vector<CBaseComponent*>	mComponents;
	CTransform2DComponent*			mTransformComponent;
	bool							mIsPendingToKill = false;

};