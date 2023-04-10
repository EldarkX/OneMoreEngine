#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

#include "SDL_events.h"

class CInputComponent : public CBaseComponent
{
public:
	virtual void	BeginPlay() override;
	virtual void	ProccessInput(const SDL_Event* event);

					~CInputComponent();
};