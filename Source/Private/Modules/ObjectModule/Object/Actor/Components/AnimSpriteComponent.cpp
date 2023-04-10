
#include "Modules/ObjectModule/Object/Actor/Components/AnimSpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"
#include "Modules/RenderModule/Texture.h"

#include <iostream>

void CAnimSpriteComponent::BeginPlay()
{
	CSpriteComponent::BeginPlay();
}

void CAnimSpriteComponent::PlayAnimation(std::string name, float playRate)
{
	if (Animations.count(name))
	{
		Animation* AnimToSet = Animations[name];
		if (!CurrentAnimation.second ||
			(AnimToSet != CurrentAnimation.second && AnimToSet->Priority >= CurrentAnimation.second->Priority))
		{
			CurrentAnimation = { name, AnimToSet };
			CurrentAnimFps = static_cast<int>(CurrentAnimation.second->AnimFps * playRate);

			CurrentFrame = 0;

			SetTexture(CurrentAnimation.second->Textures[static_cast<int>(CurrentFrame)]);

			OnAnimationStartPlay(name);
		}
	}
}

void CAnimSpriteComponent::Tick(float deltaTime)
{
	CSpriteComponent::Tick(deltaTime);

	if (CurrentAnimation.second)
	{
		CurrentFrame += CurrentAnimFps * deltaTime;

		if (CurrentFrame >= CurrentAnimation.second->TexturesAmount)
		{
			if (CurrentAnimation.second->IsLooping)
			{
				CurrentFrame -= CurrentAnimation.second->TexturesAmount;
			}
			else
			{
				OnAnimationEndPlay(CurrentAnimation.first);
				CurrentAnimation.second = nullptr;
				PlayAnimation(BaseAnimation);			
			}
		}

		SetTexture(CurrentAnimation.second->Textures[static_cast<int>(CurrentFrame)]);
	}
}

void CAnimSpriteComponent::AddAnimation(std::string name, std::string path, unsigned int framesAmount,
	unsigned int animFPS /*= 24*/, unsigned int priority /*= 0*/, bool isLooping /*= false*/)
{
	std::string zero;
	std::string new_path;

	Animation* newAnim = new Animation(animFPS, priority, isLooping);

	for (unsigned int i = 1; i <= framesAmount; ++i)
	{
		new_path = path + std::to_string(i) + ".png";
		newAnim->Textures.push_back(new OTexture(new_path.c_str()));
	}

	newAnim->TexturesAmount = newAnim->Textures.size();

	Animations.insert({ name, newAnim });
}

void CAnimSpriteComponent::SetBaseAnimation(std::string name)
{
	if (!Animations.count(name))
	{
		std::cout << "Error: can't set base animation" << std::endl;
		exit(-1);
	}

	BaseAnimation = name;

	CurrentAnimation = { name, Animations[BaseAnimation] };
}

CAnimSpriteComponent::~CAnimSpriteComponent()
{
	CurrentAnimation.second = nullptr;
	Animations.clear();

	SetTexture(nullptr);
}
