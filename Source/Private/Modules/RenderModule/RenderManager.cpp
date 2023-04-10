
#include "Modules/RenderModule/RenderManager.h"

#include "Modules/RenderModule/VertexArray.h"
#include "Modules/RenderModule/Shader.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Utils/AssetManager/AssetManagerUtils.h"

bool RenderManager::Initialize()
{
	if (!InitializeLibrary())
		return false;

	if (!CreateGameWindow())
		return false;

	if (!InitializeSpriteShader())
		return false;

	return true;
}

bool RenderManager::InitializeLibrary()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout << "RenderManager::InitializeLibrary() : Cannot init SDL" << endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	return true;
}

bool RenderManager::InitializeSpriteShader()
{
	mSpriteShader = new Shader();

	string ProjectDir = GameEngine::GetGameEngine()->GetAssetManagerUtils()->GetProjectDir();

	if (!mSpriteShader->Load(ProjectDir + "\\Assets\\Shaders\\Sprite.vert", ProjectDir + "\\Assets\\Shaders\\Sprite.frag"))
	{
		cout << "RenderManager::RenderManager() : Shader has not been loaded!" << endl;
		return false;
	}

	float vertexBuffer[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f,
		0.5f, 0.5f, 0.f, 1.f, 0.f,
		0.5f, -0.5f, 0.f, 1.f, 1.f,
		-0.5f, -0.5f, 0.f, 0.f, 1.f
	};

	unsigned int indexBuffer[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteShader->SetActive();

	mSpriteVerts = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
	mSpriteVerts->SetActive();

	Matrix4D viewProj = CreateSimpleViewProj(static_cast<float>(GameEngine::GetGameEngine()->GetWindowWidth()),
		static_cast<float>(GameEngine::GetGameEngine()->GetWindowHeight()));
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	return true;
}

bool RenderManager::CreateGameWindow()
{
	//TODO: 200 should be changed with proper settings (fullscreen, borderless, window)
	mWindow = SDL_CreateWindow("Game", 200, 200, GameEngine::GetGameEngine()->GetWindowWidth(),
		GameEngine::GetGameEngine()->GetWindowHeight(), SDL_WINDOW_OPENGL);

	if (!mWindow)
	{
		cout << "RenderManager::CreateWindow() : Cannot create SDL_Window" << endl;
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	if (!mContext)
	{
		cout << "RenderManager::CreateWindow() : Cannot create SDL_GL_Context" << endl;
		return false;
	}

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		SDL_Log("RenderManager::CreateGameWindow() : Failed to initialize GLEW.");
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == -1)
	{
		cout << "RenderManager::CreateGameWindow() : Cannot init IMG" << endl;
		return false;
	}

	return true;
}

void RenderManager::AddDrawableComponent(CSpriteComponent *NewSprite)
{
	if (mDrawableComponents.empty())
	{
		mDrawableComponents.push_back(NewSprite);
	}
	else
	{
		//TODO: binary search ( O(log(n)) instead O(n) ) 
		for (auto iter = mDrawableComponents.cbegin(); iter < mDrawableComponents.cend(); ++iter)
		{
			if (NewSprite->GetDrawOrder() < (*iter)->GetDrawOrder())
			{
				mDrawableComponents.insert(iter, NewSprite);
				return;
			}
		}
		mDrawableComponents.push_back(NewSprite);
	}
}

void RenderManager::RemoveDrawableComponent(CSpriteComponent *Sprite)
{
	mDrawableComponents.erase(find(mDrawableComponents.cbegin(), mDrawableComponents.cend(), Sprite));
}

void RenderManager::RenderWindow()
{
	DrawBackBuffer();
	DrawFrontBuffer();
	SwitchBuffers();
}

void RenderManager::DrawBackBuffer()
{
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,          // srcFactor is srcAlpha
		GL_ONE_MINUS_SRC_ALPHA // dstFactor is 1 - srcAlpha
	);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderManager::DrawFrontBuffer()
{
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();

	for (const auto& Drawable : mDrawableComponents)
	{
		Drawable->Draw(mSpriteShader);
	}
}

void RenderManager::SwitchBuffers()
{
	SDL_GL_SwapWindow(mWindow);
}

void RenderManager::Terminate()
{
	mDrawableComponents.clear();

	delete mSpriteVerts;
	delete mSpriteShader;

	if (mContext)
	{
		SDL_GL_DeleteContext(mContext);
	}

	if (mWindow)
	{
		SDL_DestroyWindow(mWindow);
	}

	SDL_Quit();
}

Matrix4D RenderManager::CreateSimpleViewProj(float width, float height)
{
	return Matrix4D({
		{ 2.0f / width, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
	});
}


