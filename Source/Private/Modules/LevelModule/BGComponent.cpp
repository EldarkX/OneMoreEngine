
#include "Modules/LevelModule/BGComponent.h"

#include "Modules/CoreModule/GameEngine.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

void BGComponent::SetTextures(const std::vector<SDL_Texture*>& Textures)
{
	int count = 0;
	for (SDL_Texture* text : Textures)
	{
		BGTexture newBGTexture;
		newBGTexture.mTexture = text;
		newBGTexture.mOffsetX = static_cast<float>(count * GameEngine::GetGameEngine()->GetWindowWidth());
		mBGTextures.push_back(newBGTexture);
		++count;
	}
}

void BGComponent::Tick(float deltaTime)
{
	for (auto bgText : mBGTextures)
	{
		bgText.mOffsetX += mScrollSpeed * deltaTime;

		if (bgText.mOffsetX < -GameEngine::GetGameEngine()->GetWindowWidth())
		{
			bgText.mOffsetX = (static_cast<int>(mBGTextures.size()) - 1) * GameEngine::GetGameEngine()->GetWindowWidth() - 1.f;
		}
	}
}

BGComponent::~BGComponent()
{
	mBGTextures.clear();
}
