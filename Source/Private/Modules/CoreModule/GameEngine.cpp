
#include "Modules/CoreModule/GameEngine.h"

#include "Modules/CoreModule/InputManager.h"
#include "Modules/PhysicsModule/CollisionManager.h"
#include "Modules/RenderModule/RenderManager.h"
#include "Utils/AssetManager/AssetManagerUtils.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

GameEngine* GameEngine::thisGameEngine = nullptr;

GameEngine::GameEngine(int window_width, int window_height)
      : WindowWidth(window_width),
	WindowHeight(window_height)
{
	//TODO: it is better to get rid of singlton conception replacing it with a global entities manager and game modes
	if (thisGameEngine)
		static_assert(1);
	else
		thisGameEngine = this;

	//TODO: replace with a settings file
	WindowHalfWidth = WindowWidth / 2;
	WindowHalfHeight = WindowHeight / 2;

	mGameStatus = EGameStatus::GSE_Game;

	if (!PreInit())
	{
		cout << "GameEngine->PreInit() has been failed. Terminate." << endl;
		delete this;
		exit(-1);
	}
};

bool GameEngine::PreInit()
{
	//Create main subsystems
	mAssetManagerUtils = new AssetManagerUtils();
	if (!mAssetManagerUtils)
	{
		cout << "GameEngine::PreInit() : Failed to create AssetManagerUtils" << endl;
		return false;
	}
	Subsystems.push_back(mAssetManagerUtils);

	mRenderManager = new RenderManager();
	if (!mRenderManager)
	{
		cout << "GameEngine::PreInit() : Failed to create RenderManager" << endl;
		return false;
	}
	Subsystems.push_back(mRenderManager);

	mCollisionManager = new CollisionManager();
	if (!mCollisionManager)
	{
		cout << "GameEngine::PreInit() : Failed to create CollisionManager" << endl;
		return false;
	}
	Subsystems.push_back(mCollisionManager);

	mInputManager = new InputManager();
	if (!mInputManager)
	{
		cout << "GameEngine::PreInit() : Failed to create InputManager" << endl;
		return false;
	}
	Subsystems.push_back(mInputManager);
	
	//Subsystems initialization
	for (const auto& Subsystem : Subsystems)
	{
		if (!Subsystem->Initialize())
		{
			return false;
		}
	}
	return true;
}

//Update Method pattern
void GameEngine::Tick()
{
    auto			mTicksCount = SDL_GetTicks();
	double			second = 0.f;

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
			++nbFrames;

			second += DeltaTime;

			if (second >= 1)
			{
				second = 0.f;
				cout << "FPS: " << nbFrames << endl;
				nbFrames = 0;
			}
		}

	    // INPUT HANDLE
		//TODO: use another thread and library
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
			mRenderManager->RenderWindow();
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

	while (Subsystems.size())
	{
		auto* Subsystem = Subsystems[0];
		Subsystems.erase(find(Subsystems.begin(), Subsystems.end(), Subsystem));
		Subsystem->Terminate();
		delete Subsystem;
	}
}

