
#include "Modules/ObjectModule/Object/Components/InputComponent.h"

#include "Modules/CoreModule/InputManager.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

void CInputComponent::BeginPlay()
{
	GameEngine::GetGameEngine()->GetInputManager()->AddInputComponent(this);
}

void CInputComponent::ProccessInput(const SDL_Event* event)
{
	if (event->type == SDL_QUIT || event->key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE)
	{
		GameEngine::GetGameEngine()->SetGameStatus(EGameStatus::GSE_Exit);
	}
}

CInputComponent::~CInputComponent()
{
	GameEngine::GetGameEngine()->GetInputManager()->RemoveInputComponent(this);
}


