#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include <algorithm>

AActor::AActor()
{
	//RootComponent = AddComponent<CTransform2DComponent>();
}

void AActor::BeginPlay() {}

void AActor::Tick(float deltaTime)
{
	for (auto Comp : mComponents)
	{
		Comp->Tick(deltaTime);
	}
}

void AActor::SetRootComponent(CTransform2DComponent* NewRoot)
{
	static bool OverridenRoot = false;

	if (!OverridenRoot)
	{
		//delete RootComponent;
		OverridenRoot = true;
	}
	RootComponent = NewRoot;
}

void AActor::RemoveComponent(CBaseComponent* Component)
{
	mComponents.erase(find(mComponents.cbegin(), mComponents.cend(), Component));
	delete Component;
}

void AActor::SetActorPosition(Vector2D InPosition)
{
	RootComponent->SetRelativePosition(InPosition);
}

void AActor::SetActorRotationAngle(float InRotationAngle)
{
	RootComponent->SetRelativeRotationAngle(InRotationAngle);
}

void AActor::SetActorScale(Vector2D InScale)
{
	RootComponent->SetRelativeScale(InScale);
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
		RemoveComponent(mComponents.back());

	OnStartBeingPendingToKill.Clear();
}
