#pragma once

#include "Modules/CoreModule/GameEngine.h"

using std::string;

class AssetsManagerUtils
{

public:

	string GetProjectDir()
	{
		if (mProjectDir.empty())
		{
			char result[MAX_PATH];

			GetModuleFileName(NULL, result, MAX_PATH);

			std::string ProjectPath(result);

			ProjectPath.erase(ProjectPath.find("\\x64\\"));

			mProjectDir = ProjectPath;
		}
		return mProjectDir;
	}

private:

	string mProjectDir = "";
};