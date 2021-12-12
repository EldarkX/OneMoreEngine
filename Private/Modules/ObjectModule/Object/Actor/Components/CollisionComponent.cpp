
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Modules/CoreModule/CollisionManager.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

void CCollisionComponent::TriggerCollision(class AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent)
{
	OnComponentCollided(AnotherActor, AnotherCollisionComponent);
}

void CCollisionComponent::BeginPlay()
{
	GameEngine::GetGameEngine()->GetCollisionManager().AddAgent(this);
}

void CCollisionComponent::SetCollisionResponseToChannel(ECollisionChannel CollisionChannel, ECollisionType newResponse)
{
	mCollisionResponses->at(CollisionChannel) = newResponse;
}

void CCollisionComponent::SetCollisionResponseToAllChannels(ECollisionType newResponse)
{
	for (auto &ResponseToChannel : *mCollisionResponses)
	{
		ResponseToChannel.second = newResponse;
	}
}

bool CCollisionComponent::CanCollidedWith(CCollisionComponent* otherComp)
{
	return otherComp->GetCollisionResponses()->find(mCollisionChannel)->second == ECollisionType::CTE_Collide;
}

bool CCollisionComponent::IsCollisionEnabled()
{
	for (const auto &ResponseToChannel : *mCollisionResponses)
	{
		if (ResponseToChannel.second == ECollisionType::CTE_Collide)
			return true;
	}
	return false;
}

CCollisionComponent::~CCollisionComponent()
{
	GameEngine::GetGameEngine()->GetCollisionManager().RemoveAgent(this);
}
