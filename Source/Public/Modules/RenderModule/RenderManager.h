#pragma once

#include "Modules/CoreModule/Subsystem.h"

class CSpriteComponent;
class VertexArray;
class Shader;

class RenderManager : public Subsystem
{
public:
	RenderManager() {}

	virtual bool					Initialize() override;

	void							AddDrawableComponent(CSpriteComponent *drawableComponent);
	void							RemoveDrawableComponent(CSpriteComponent * drawableComponent);

	void							RenderWindow();

	inline SDL_Window*				GetWindow() const { return mWindow; }

	virtual void					Terminate() override;

protected:
	bool							InitializeLibrary();
	bool							InitializeSpriteShader();

	bool							CreateGameWindow();

	void							DrawBackBuffer();
	void							DrawFrontBuffer();
	void							SwitchBuffers();

	Matrix4D						CreateSimpleViewProj(float width, float height);

protected:
	SDL_Window*						mWindow = nullptr;
	SDL_GLContext					mContext = nullptr;

	vector<CSpriteComponent*>		mDrawableComponents;

	VertexArray*					mSpriteVerts = nullptr;
	Shader*							mSpriteShader = nullptr;
};