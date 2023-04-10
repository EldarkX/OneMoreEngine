#pragma once

#include "Modules/CoreModule/Subsystem.h"

//TODO: this class will be responsible for assets loading and storing references to them when level editor is written

class AssetManagerUtils : public Subsystem
{
public:
	virtual bool	Initialize() override;
	virtual void	Terminate() override;

	string			GetProjectDir();
private:
	string			mProjectDir = "";
};
