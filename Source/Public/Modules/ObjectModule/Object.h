#pragma once

#include "Modules/CoreModule/GameEngine.h"

class OObject
{

public:

	OObject();

	virtual	void				BeginPlay();


	virtual void				Tick(float deltaTime);

	string						GetObjectName() const { return mObjectName; }
	void						SetObjectName(string objName) { mObjectName = objName; }

	virtual void				Destroy();

	virtual ~OObject() {};

	//MulticastDelegate1<OObject*> OnDestroyed;

protected:

	string						mObjectName;

};
