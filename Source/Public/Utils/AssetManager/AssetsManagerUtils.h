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
			_fullpath(result, "", _MAX_PATH);
			mProjectDir = result;
		}
		return mProjectDir;
	}

private:

	string mProjectDir = "";
};