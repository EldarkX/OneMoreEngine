#pragma once

#include "Modules/CoreModule/GameEngine.h"

class CInputComponent;

class InputManager
{

public:

	void    HandleInput(const SDL_Event* event);

	void	AddInputComponent(CInputComponent*);
	void	RemoveInputComponent(CInputComponent*);

private:

	vector<CInputComponent*> mInputComponents;

};

