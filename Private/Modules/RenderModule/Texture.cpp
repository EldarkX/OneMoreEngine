
#include "Modules/RenderModule/Texture.h"

Texture::Texture(const std::string& path)
{
	Load(path);
}

bool Texture::Load(const std::string& path)
{
	SDL_Surface* Image;
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

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

Texture::~Texture()
{
	Unload();
}

