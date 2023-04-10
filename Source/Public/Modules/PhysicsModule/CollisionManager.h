#pragma once

#include "Modules/CoreModule/Subsystem.h"

#include <vector>

class CCollisionComponent;

class CollisionManager : public Subsystem
{
public:
	virtual bool	Initialize() override;

	void			AddAgent(CCollisionComponent* Agent);
	void			RemoveAgent(CCollisionComponent* Agent);

    void			CheckAllCollisions();

	virtual void	Terminate() override;
protected:
	bool			AreCollided(CCollisionComponent* Agent1, CCollisionComponent* Agent2);

private:
    std::vector<CCollisionComponent*>	Agents;
};

