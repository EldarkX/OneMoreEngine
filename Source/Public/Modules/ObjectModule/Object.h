#pragma once

#include "Modules/CoreModule/GameEngine.h"

class OObject
{
public:
	OObject() = default;

	virtual	void				BeginPlay() = 0;
	virtual void				Tick(float deltaTime) = 0;

	inline string				GetObjectName() const { return mObjectName; }
	inline void					SetObjectName(string objName) { mObjectName = objName; }

	virtual void				Destroy() = 0;

	virtual						~OObject(){}
protected:
	string						mObjectName;
};
