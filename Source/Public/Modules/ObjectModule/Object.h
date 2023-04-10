#pragma once

#include <string>

class OObject
{
public:
	OObject() = default;

	virtual	void				BeginPlay() = 0;
	virtual void				Tick(float deltaTime) = 0;

	inline std::string			GetObjectName() const { return mObjectName; }
	inline void					SetObjectName(std::string objName) { mObjectName = objName; }

	virtual void				Destroy() = 0;

	virtual						~OObject(){}
protected:
	std::string					mObjectName;
};
