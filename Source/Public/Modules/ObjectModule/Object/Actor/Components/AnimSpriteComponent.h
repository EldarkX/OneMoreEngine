#pragma once

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

class OTexture;

struct Animation
{
	Animation(unsigned int animFPS, unsigned int priority, bool isLooping)
		: AnimFps(animFPS), Priority(priority), IsLooping(isLooping) {};

	unsigned int						AnimFps = 24;
	unsigned int						Priority = 0;
	vector<OTexture*>					Textures;
	size_t								TexturesAmount = 0;
	bool								IsLooping = true;

	~Animation();
};

class CAnimSpriteComponent : public CSpriteComponent
{
public:
	int											GetAnimFPS() const { return CurrentAnimFps; }
	void										SetAnimFPS(int AnimFPS) { CurrentAnimFps = AnimFPS; }

	virtual void								Tick(float deltaTime) override;

	void										AddAnimation(string name, string path, unsigned int framesAmount, unsigned int animFPS = 24,
													unsigned int priority = 0, bool isLooping = false);

	void										SetBaseAnimation(string name);

	void										PlayAnimation(string name, float playRate = 1.f);

	MulticastDelegate1<string>					OnAnimationStartPlay;
	MulticastDelegate1<string>					OnAnimationEndPlay;

	virtual void								BeginPlay() override;

	~CAnimSpriteComponent();
protected:
	std::map<string, Animation*>				Animations;
	
	std::pair<string, Animation*>				CurrentAnimation;
	string										BaseAnimation;

	int											CurrentAnimFps = 24;
	float										CurrentFrame = 0;
};