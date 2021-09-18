#pragma once

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

class Texture;

struct Animation
{
	Animation(unsigned int animFPS, unsigned int priority, bool isLooping)
		: mAnimFps(animFPS), mPriority(priority), mIsLooping(isLooping) {};

	unsigned int						mAnimFps = 24;
	unsigned int						mPriority = 0;
	vector<Texture*>					mTextures;
	size_t								mTexturesAmount = 0;
	bool								mIsLooping = true;

	~Animation();
};

class CAnimSpriteComponent : public CSpriteComponent
{

public:
	int											GetAnimFPS() const { return mCurrentAnimFps; }
	void										SetAnimFPS(int AnimFPS) { mCurrentAnimFps = AnimFPS; }

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
	std::map<string, shared_ptr<Animation>>		mAnimations;
	
	std::pair<string, shared_ptr<Animation>>	mCurrentAnimation;
	string										mBaseAnimation;

	int											mCurrentAnimFps = 24;
	float										mCurrentFrame = 0;
};