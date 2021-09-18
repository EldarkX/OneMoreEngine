#pragma once

#include "Modules/CoreModule/GameEngine.h"

class RenderManager
{

public:

	RenderManager(GameEngine *gameEngine);

	void							DrawBackBuffer();

	void							DrawFrontBuffer();

	void							SwitchBuffers();

	void							AddDrawableComponent(class CSpriteComponent *);

	void							RemoveDrawableComponent(class CSpriteComponent *);

	Matrix4D						CreateSimpleViewProj(float width, float height);

	virtual							~RenderManager();

private:

	vector<class CSpriteComponent *>	mDrawableComponents;

	class VertexArray				*mSpriteVerts;
	class Shader					*mSpriteShader;

	GameEngine						*mGameEngine;
};