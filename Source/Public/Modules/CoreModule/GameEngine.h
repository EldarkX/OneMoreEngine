#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "glew.h"

#include <Windows.h>

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <memory>
#include <assert.h>

#include "Modules/MathModule/Vector2D.h"
#include "Modules/MathModule/Matrix4.h"

#include "DataTypes.h"

#include "Utils/Delegate/MulticastDelegate.h"

using namespace DelegateLib;

using std::cout;
using std::endl;
using std::vector;
using std::string;

using std::to_string;

using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using std::make_unique;
using std::weak_ptr;

#define  DEBUG_COLLISIONS 0
#define  DEBUG_SHOW_FPS 1

class CollisionManager;
class RenderManager;
class InputManager;
class AssetManagerUtils;
class Subsystem;
class AActor;

class GameEngine
{
public:
	GameEngine(int window_width, int window_height);
	GameEngine(GameEngine& gameEngine) = delete;
	GameEngine(GameEngine&& gameEngine) = delete;
	
	void operator=(const GameEngine& gameEngine) = delete;
	void operator=(const GameEngine&& gameEngine) = delete;

	bool							PreInit();
	virtual bool					Init() = 0;
	virtual void					Tick();

	CollisionManager*				GetCollisionManager() const { return mCollisionManager; }
	RenderManager*					GetRenderManager() const { return mRenderManager; }
	InputManager*					GetInputManager() const { return mInputManager; }
	AssetManagerUtils*				GetAssetManagerUtils() const { return mAssetManagerUtils; }

	inline int						GetWindowWidth() const { return WindowWidth; }
	inline int						GetWindowHeight() const { return WindowHeight; }
	inline int						GetWindowHalfWidth() const { return WindowHalfWidth; }
	inline int						GetWindowHalfHeight() const { return WindowHalfHeight; }

	const EGameStatus				GetGameStatus() const { return mGameStatus; }
	void							SetGameStatus(EGameStatus newGameStatus) { mGameStatus = newGameStatus; }

	void							AddActor(AActor * ActorToAdd);
	void							RemoveActor(AActor * ActorToRemove);

	void							AddObjectToKill(AActor* ActorToKill);
	void							KillActors();

	static GameEngine				*GetGameEngine();

	template<class T>
	T* CreateActor(Vector2D ActorPosition, Vector2D ActorSize, string ObjectName)
	{
		AActor* NewActor = new T();
		NewActor->SetObjectName(ObjectName);

		NewActor->SetActorPosition(ActorPosition);
		NewActor->SetActorScale(ActorSize);

		NewActor->OnStartBeingPendingToKill += MakeDelegate(this, &GameEngine::AddObjectToKill);

		NewActor->BeginPlay();

		AddActor(NewActor);

		return dynamic_cast<T *>(NewActor);
	}

	virtual							~GameEngine();

protected:
	EGameStatus						mGameStatus;

	float							DeltaTime;

	bool							mIsActorsUpdating = false;

	//TODO: replace with OpenGL/DirectX
    SDL_Event						event;

	//TODO: make a settings file
    int								WindowWidth;
    int								WindowHeight;
	int								WindowHalfWidth;
	int								WindowHalfHeight;

    vector<AActor *>				Actors;
	vector<AActor *>				NewActors;
	vector<AActor *>				ActorsToKill;

	CollisionManager				*mCollisionManager = nullptr;
	RenderManager					*mRenderManager = nullptr;
	InputManager					*mInputManager = nullptr;
	AssetManagerUtils				*mAssetManagerUtils = nullptr;

	vector<Subsystem*>				Subsystems;

	static GameEngine				*thisGameEngine;
};