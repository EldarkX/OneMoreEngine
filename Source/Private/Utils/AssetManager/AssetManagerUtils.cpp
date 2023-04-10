
#include "Utils/AssetManager/AssetManagerUtils.h"

bool AssetManagerUtils::Initialize()
{
	return true;
}

std::string AssetManagerUtils::GetProjectDir()
{
	if (mProjectDir.empty())
	{
		char result[_MAX_PATH];
		auto fullpath = _fullpath(result, "", _MAX_PATH);
		mProjectDir = result;
	}
	return mProjectDir;
}

void AssetManagerUtils::Terminate() {}
