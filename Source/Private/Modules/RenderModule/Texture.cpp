
#include "Modules/RenderModule/Texture.h"

#include "glew.h"
#include <SDL_image.h>

OTexture::OTexture(const std::string& path)
{
	Load(path);
}

bool OTexture::Load(const std::string& path)
{
	SDL_Surface* Image;
	//TODO: replace with a proper loading system -> AssetManagerUtils
	Image = IMG_Load(path.c_str());
	if (!Image)
	{
		SDL_Log("Texture::Load: SOIL failed to load image %s", path.c_str());
		return false;
	}
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image->w, Image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	mWidth = Image->w;
	mHeight = Image->h;
	SDL_FreeSurface(Image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void OTexture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void OTexture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

OTexture::~OTexture()
{
	Unload();
}
