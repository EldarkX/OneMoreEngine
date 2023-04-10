#pragma once

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include "Utils/Delegate/MulticastDelegate.h"

#include <vector>
#include <map>
#include <string>

class OTexture;

struct Animation
{
	Animation(unsigned int animFPS, unsigned int priority, bool isLooping)
		: AnimFps(animFPS), Priority(priority), IsLooping(isLooping) {}

	unsigned int						AnimFps = 24;
	unsigned int						Priority = 0;
	std::vector<OTexture*>				Textures;
	size_t								TexturesAmount = 0;
	bool								IsLooping = true;

										~Animation() {}
};

class CAnimSpriteComponent : public CSpriteComponent
{
public:
	virtual void								BeginPlay() override;
	virtual void								Tick(float deltaTime) override;

	int											GetAnimFPS() const { return CurrentAnimFps; }
	void										SetAnimFPS(int AnimFPS) { CurrentAnimFps = AnimFPS; }
	void										AddAnimation(std::string name, std::string path, unsigned int framesAmount, unsigned int animFPS = 24,
													unsigned int priority = 0, bool isLooping = false);
	void										SetBaseAnimation(std::string name);
	void										PlayAnimation(std::string name, float playRate = 1.f);
												~CAnimSpriteComponent();
public:
	DelegateLib::MulticastDelegate1<std::string>	OnAnimationStartPlay;
	DelegateLib::MulticastDelegate1<std::string>	OnAnimationEndPlay;
protected:
	std::map<std::string, Animation*>			Animations;
	
	std::pair<std::string, Animation*>			CurrentAnimation;
	std::string									BaseAnimation;

	int											CurrentAnimFps = 24;
	float										CurrentFrame = 0;
};