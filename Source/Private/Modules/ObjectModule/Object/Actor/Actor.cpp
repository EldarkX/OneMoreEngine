
#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/CoreModule/GameEngine.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

AActor::AActor()
{
	mTransformComponent = AddComponent<CTransform2DComponent>();
}

void AActor::BeginPlay() {}

void AActor::Tick(float deltaTime)
{
	for (const auto &Comp : mComponents)
	{
		Comp->Tick(deltaTime);
	}
}

Vector2D AActor::GetActorPosition() const
{
	return mTransformComponent->GetPosition();
}

Vector2D AActor::GetActorScale() const
{
	return mTransformComponent->GetScale();
}

void AActor::SetActorPosition(Vector2D newPosition)
{
	mTransformComponent->SetPosition(newPosition);
}

void AActor::SetActorScale(Vector2D newScale)
{
	mTransformComponent->SetScale(newScale);
}

void AActor::RemoveComponent(CBaseComponent* Component)
{
	mComponents.erase(find(mComponents.cbegin(), mComponents.cend(), Component));
	delete Component;
}

void AActor::SetIsPendingToKill(bool newIsPendingToKill)
{
	mIsPendingToKill = newIsPendingToKill;

	if (mIsPendingToKill)
	{
		OnStartBeingPendingToKill(this);
	}
}

void AActor::Destroy()
{
	GameEngine::GetGameEngine()->RemoveActor(this);
}

AActor::~AActor()
{
	while (!mComponents.empty())
	{
		RemoveComponent(mComponents[0]);
	}

	OnStartBeingPendingToKill.Clear();
}
