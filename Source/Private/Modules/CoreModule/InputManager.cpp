
#include "Modules/CoreModule/InputManager.h"

#include "Modules/ObjectModule/Object/Components/InputComponent.h"

bool InputManager::Initialize()
{
	return true;
}

void InputManager::HandleInput(const SDL_Event *event)
{
	for (const auto &Input : mInputComponents)
	{
		Input->ProccessInput(event);
	}
}

void InputManager::AddInputComponent(CInputComponent *Input)
{
	mInputComponents.push_back(Input);
}

void InputManager::RemoveInputComponent(CInputComponent* Input)
{
	mInputComponents.erase(find(mInputComponents.cbegin(), mInputComponents.cend(), Input));
}

void InputManager::Terminate()
{
	mInputComponents.clear();
}
