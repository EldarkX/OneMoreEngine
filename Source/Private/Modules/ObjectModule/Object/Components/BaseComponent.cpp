
#include "Modules/ObjectModule/Object/Components/BaseComponent.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

void CBaseComponent::Tick(float deltaTime) { }

void CBaseComponent::BeginPlay() {}

void CBaseComponent::Destroy()
{
	GetOwner()->RemoveComponent(this);
}
