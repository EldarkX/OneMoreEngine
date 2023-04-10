#pragma once

#include "Modules/ObjectModule/Object.h"

class CBaseComponent : public OObject
{
public:
	virtual void		Tick(float deltaTime) override;

	class AActor		*GetOwner() const { return mOwner; }
	void				SetOwner(class AActor *newOwner) { mOwner = newOwner; }

	virtual void		BeginPlay() override;

	virtual void		Destroy() override;

protected:
	class AActor		*mOwner;
};