#pragma once

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

class BGComponent : public CSpriteComponent
{

public:

	virtual void				Tick(float deltaTime) override;

	void						SetTextures(const vector<SDL_Texture*>& Textures);

	float						GetScrollSpeed() const { return mScrollSpeed; }
	void						SetScrollSpeed(float ScrollSpeed) { mScrollSpeed = ScrollSpeed; }

private:

	struct BGTexture
	{
		SDL_Texture				*mTexture;
		float					mOffsetX;
	};
	vector<BGTexture>			mBGTextures;

	float						mScrollSpeed = 5.;

};