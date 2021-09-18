#pragma once

#include "GameEngine.h"

class CollisionManager
{

public:

	void AddAgent(class CCollisionComponent *Agent);
	void RemoveAgent(class CCollisionComponent *Agent);

    void CheckAllCollisions();

private:

	bool AreCollided(class CCollisionComponent *Agent1, class CCollisionComponent *Agent2);

    vector<class CCollisionComponent*> Agents;
};

