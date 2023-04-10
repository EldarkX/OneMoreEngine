#pragma once

#include "Modules/CoreModule/GameEngine.h"

class OTexture
{
public:
					OTexture() {};
					OTexture(const string& path);

	bool			Load(const string& path);
	void			Unload();

	void			SetActive();

	int				GetWidth() const { return mWidth; }
	int				GetHeight() const { return mHeight; }
	
					~OTexture();
private:
	unsigned int	mTextureID = 0;

	int				mWidth = 0;
	int				mHeight = 0;
};