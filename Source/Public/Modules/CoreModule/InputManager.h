#pragma once

#include "Modules/CoreModule/Subsystem.h"

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
	vector<CInputComponent*> mInputComponents;
};

