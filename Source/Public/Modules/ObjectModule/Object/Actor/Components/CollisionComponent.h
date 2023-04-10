#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

#include "Modules/CoreModule/DataTypes.h"
#include "Utils/Delegate/MulticastDelegate.h"

#include <map>

class CCollisionComponent;
class AActor;

class CCollisionComponent : public CBaseComponent
{
public:
	virtual void								BeginPlay() override;

	ECollisionChannel							GetCollisionChannel() const { return mCollisionChannel; }
	void										SetCollisionChannel(ECollisionChannel newChannel) { mCollisionChannel = newChannel; }

	std::map<ECollisionChannel, ECollisionType>* GetCollisionResponses() const { return mCollisionResponses; }
	void										SetCollisionResponseToChannel(ECollisionChannel CollisionChannel, ECollisionType newResponse);
	void										SetCollisionResponseToAllChannels(ECollisionType newResponse);
	bool										CanCollidedWith(CCollisionComponent* otherComp);
	bool										IsCollisionEnabled();

	void										TriggerCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent);

	~CCollisionComponent();

public:
	DelegateLib::MulticastDelegate2<AActor*, CCollisionComponent*>	OnComponentCollided;
private:
	std::map<ECollisionChannel, ECollisionType>* mCollisionResponses = new std::map<ECollisionChannel, ECollisionType>
	{
		{ECollisionChannel::CCE_StaticObject1,	ECollisionType::CTE_Ignore},
		{ECollisionChannel::CCE_StaticObject2,	ECollisionType::CTE_Ignore},
		{ECollisionChannel::CCE_StaticObject3,	ECollisionType::CTE_Ignore},
		{ECollisionChannel::CCE_DynamicObject1,	ECollisionType::CTE_Ignore},
		{ECollisionChannel::CCE_DynamicObject2,	ECollisionType::CTE_Ignore},
		{ECollisionChannel::CCE_DynamicObject3,	ECollisionType::CTE_Ignore},
		{ECollisionChannel::CCE_Player,			ECollisionType::CTE_Ignore}
	};

	ECollisionChannel							mCollisionChannel = ECollisionChannel::CCE_StaticObject1;
};