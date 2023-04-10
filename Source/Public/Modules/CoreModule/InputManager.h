#pragma once

#include "Modules/CoreModule/Subsystem.h"

#include <vector>

#include "SDL.h"

class CInputComponent;

class InputManager : public Subsystem
{
public:
	virtual bool	Initialize() override;

	void			HandleInput(const SDL_Event* event);

	void			AddInputComponent(CInputComponent*);
	void			RemoveInputComponent(CInputComponent*);

	virtual void	Terminate() override;
private:
	std::vector<CInputComponent*>	mInputComponents;
};

