#pragma once

#include "Modules/CoreModule/GameEngine.h"
#include <string>

class Texture
{

public:

	Texture() {};
	Texture(const std::string& path);

	bool			Load(const std::string& path);
	void			Unload();

	void			SetActive();

	int				GetWidth() const { return mWidth; }
	int				GetHeight() const { return mHeight; }
	
	~Texture();

private:

	unsigned int	mTextureID = 0;

	int				mWidth = 0;
	int				mHeight = 0;

};