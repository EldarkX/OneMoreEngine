#pragma once

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include <vector>

#include "SDL.h"
#include "SDL_image.h"

class BGComponent : public CSpriteComponent
{
public:
	virtual void				Tick(float deltaTime) override;

	void						SetTextures(const std::vector<SDL_Texture*>& Textures);

	float						GetScrollSpeed() const { return mScrollSpeed; }
	void						SetScrollSpeed(float ScrollSpeed) { mScrollSpeed = ScrollSpeed; }

								~BGComponent();
private:
	//TODO: shared textures are vital for performance
	struct BGTexture
	{
		SDL_Texture*			mTexture;
		float					mOffsetX;
	};
	std::vector<BGTexture>		mBGTextures;

	float						mScrollSpeed = 5.;
};