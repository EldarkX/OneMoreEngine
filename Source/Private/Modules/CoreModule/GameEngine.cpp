
#include "Modules/CoreModule/GameEngine.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/CoreModule/CollisionManager.h"
#include "Modules/RenderModule/RenderManager.h"
#include "Modules/CoreModule/InputManager.h"

GameEngine* GameEngine::thisGameEngine = nullptr;

GameEngine::GameEngine(int window_width, int window_height)
      : WindowWidth(window_width),
	WindowHeight(window_height)
{
	WindowHalfWidth = WindowWidth / 2;
	WindowHalfHeight = WindowHeight / 2;

	mGameStatus = EGameStatus::GSE_Game;
	if (PreInit() == -1)
	{
		delete this;
		exit(-1);
	}

	if (thisGameEngine)
		static_assert(1);
	else
		thisGameEngine = this;
};

int GameEngine::PreInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout << "Can't init SDL" << endl;
		return -1;
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
	
	mWindow = SDL_CreateWindow("Game", 200, 200, WindowWidth, WindowHeight, SDL_WINDOW_OPENGL);

	if (!mWindow)
	{
		cout << "Can't create SDL_Window" << endl;
		return -1;
	}

	mContext = SDL_GL_CreateContext(mWindow);
	
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	mAssetsManagerUtils = new AssetsManagerUtils();
	assert(mAssetsManagerUtils != nullptr);

	mRenderManager = new RenderManager(this);
	assert(mRenderManager != nullptr);

	if (IMG_Init(IMG_INIT_PNG) == -1)
	{
		cout << "Can't init IMG" << endl;
		return -1;
	}

	mCollisionManager = make_unique<CollisionManager>();

	mInputManager = new InputManager();
	assert(mInputManager != nullptr);

	return 1;
}

void GameEngine::Tick()
{
    auto			mTicksCount = SDL_GetTicks();
	auto			second = 0.;

    unsigned int	nbFrames = 0; 

    while (mGameStatus != EGameStatus::GSE_Exit)
    {
		// DELTA TIME CALCULATION
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 1));
		DeltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
		DeltaTime = DeltaTime > 0.05f ? 0.05f : DeltaTime;
		mTicksCount = SDL_GetTicks();

		if (DEBUG_SHOW_FPS)
		{
			nbFrames++;

			second += DeltaTime;

			if (second >= 1)
			{
				second = 0.;
				cout << "FPS: " << nbFrames << endl;
				nbFrames = 0;
			}
		}

	    // INPUT HANDLE
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE)
			{
				GameEngine::GetGameEngine()->SetGameStatus(EGameStatus::GSE_Exit);
			}
			mInputManager->HandleInput(&event);
		}

		if (mGameStatus != EGameStatus::GSE_Pause)
		{
			//COLLISION HANDLE	
			mCollisionManager->CheckAllCollisions();

			//OBJECTS UPDATE
			mIsActorsUpdating = true;
			for (auto *Actor : Actors)
			{
				Actor->Tick(DeltaTime);
			}
			mIsActorsUpdating = false;

			for (auto &newActor : NewActors)
			{
				Actors.push_back(newActor);
			}

			NewActors.clear();

			KillActors();
			
			//DRAWING
			mRenderManager->DrawBackBuffer();
			mRenderManager->DrawFrontBuffer();
			mRenderManager->SwitchBuffers();
		}
    }
}

void GameEngine::RemoveActor(AActor * ActorToRemove)
{
	Actors.erase(find(Actors.begin(), Actors.end(), ActorToRemove));
	delete ActorToRemove;
}

void GameEngine::AddActor(AActor * ActorToAdd)
{
	if (mIsActorsUpdating)
		NewActors.push_back(ActorToAdd);
	else
		Actors.push_back(ActorToAdd);
}

void GameEngine::AddObjectToKill(AActor * ActorToKill)
{
	ActorsToKill.push_back(ActorToKill);
}

void GameEngine::KillActors()
{
	for (AActor *Actor : ActorsToKill)
		RemoveActor(Actor);
	ActorsToKill.clear();
}

GameEngine *GameEngine::GameEngine::GetGameEngine()
{
	return thisGameEngine;
}

GameEngine::~GameEngine()
{
	Actors.clear();
	NewActors.clear();

	if (mAssetsManagerUtils)
		delete mAssetsManagerUtils;

	if (mRenderManager)
		delete mRenderManager;

	if (mInputManager)
		delete mInputManager;

	if (mContext)
		SDL_GL_DeleteContext(mContext);

	if (mWindow)
		SDL_DestroyWindow(mWindow);

	SDL_Quit();
}

