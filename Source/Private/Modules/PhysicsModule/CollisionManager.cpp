
#include "Modules/PhysicsModule/CollisionManager.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Modules/MathModule/Vector2D.h"

#include <algorithm>

bool CollisionManager::Initialize()
{
	return true;
}

void CollisionManager::AddAgent(CCollisionComponent* Agent)
{
	Agents.push_back(Agent);
}

void CollisionManager::RemoveAgent(CCollisionComponent* Agent)
{
	Agents.erase(find(Agents.cbegin(), Agents.cend(), Agent));
}

//TODO: Should be optimized
void CollisionManager::CheckAllCollisions()
{
	int AgentsAmount = static_cast<int>(Agents.size());
	int FirstAgentIndex = 0;
	int SecondAgentIndex = 1;
	for (auto &FirstAgent : Agents)
	{
		SecondAgentIndex = FirstAgentIndex;
		if (FirstAgent->GetOwner()->GetIsPendingToKill() || !FirstAgent->IsCollisionEnabled())
			continue;
		while (++SecondAgentIndex < AgentsAmount)
		{
			auto SecondAgent = Agents[SecondAgentIndex];
			if (SecondAgent->GetOwner()->GetIsPendingToKill() || !SecondAgent->IsCollisionEnabled())
				continue;
			if (FirstAgent->CanCollidedWith(SecondAgent) && AreCollided(FirstAgent, SecondAgent))
			{	
				FirstAgent->TriggerCollision(SecondAgent->GetOwner(), SecondAgent);
				SecondAgent->TriggerCollision(FirstAgent->GetOwner(), FirstAgent);
			}
		}
	}
}

//TODO: There is probably a better algorithms
bool CollisionManager::AreCollided(CCollisionComponent* Agent1, CCollisionComponent* Agent2)
{
	Vector2D LeftUp1;
	LeftUp1.X() = Agent1->GetOwner()->GetActorPosition().X() - Agent1->GetOwner()->GetActorSize().X() / 2;
	LeftUp1.Y() = Agent1->GetOwner()->GetActorPosition().Y() + Agent1->GetOwner()->GetActorSize().Y() / 2;
	Vector2D RightBottom1;
	RightBottom1.X() = Agent1->GetOwner()->GetActorPosition().X() + Agent1->GetOwner()->GetActorSize().X() / 2;
	RightBottom1.Y() = Agent1->GetOwner()->GetActorPosition().Y() - Agent1->GetOwner()->GetActorSize().Y() / 2;
	Vector2D LeftUp2;
	LeftUp2.X() = Agent2->GetOwner()->GetActorPosition().X() - Agent2->GetOwner()->GetActorSize().X() / 2;
	LeftUp2.Y() = Agent2->GetOwner()->GetActorPosition().Y() + Agent2->GetOwner()->GetActorSize().Y() / 2;
	Vector2D RightBottom2;
	RightBottom2.X() = Agent2->GetOwner()->GetActorPosition().X() + Agent2->GetOwner()->GetActorSize().X() / 2;
	RightBottom2.Y() = Agent2->GetOwner()->GetActorPosition().Y() - Agent2->GetOwner()->GetActorSize().Y() / 2;
	
	if (LeftUp1.X() <= RightBottom2.X() && RightBottom1.X() >= LeftUp2.X() &&
		LeftUp1.Y() >= RightBottom2.Y() && RightBottom1.Y() <= LeftUp2.Y())
	{
		return true;
	}
	return false;
}

void CollisionManager::Terminate()
{
	Agents.clear();
}

