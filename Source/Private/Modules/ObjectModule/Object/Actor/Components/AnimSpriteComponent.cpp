
#include "Modules/ObjectModule/Object/Actor/Components/AnimSpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"
#include "Modules/RenderModule/Texture.h"

void CAnimSpriteComponent::PlayAnimation(string name, float playRate)
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

void CAnimSpriteComponent::AddAnimation(string name, string path, unsigned int framesAmount,
	unsigned int animFPS /*= 24*/, unsigned int priority /*= 0*/, bool isLooping /*= false*/)
{
	string zero;
	string new_path;

	Animation* newAnim = new Animation(animFPS, priority, isLooping);

	for (unsigned int i = 1; i <= framesAmount; ++i)
	{
		new_path = path + std::to_string(i) + ".png";
		newAnim->Textures.push_back(new OTexture(new_path.c_str()));
	}

	newAnim->TexturesAmount = newAnim->Textures.size();

	Animations.insert({ name, newAnim });
}

void CAnimSpriteComponent::SetBaseAnimation(string name)
{
	if (!Animations.count(name))
	{
		cout << "Error: can't set base animation" << endl;
		exit(-1);
	}

	BaseAnimation = name;

	CurrentAnimation = { name, Animations[BaseAnimation] };
}

void CAnimSpriteComponent::BeginPlay()
{
	CSpriteComponent::BeginPlay();
}

CAnimSpriteComponent::~CAnimSpriteComponent()
{
	CurrentAnimation.second = nullptr;
	Animations.clear();

	SetTexture(nullptr);
}

Animation::~Animation()
{
}
