#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class CInputComponent : public CBaseComponent
{

public:

	virtual void BeginPlay() override;
	virtual void ProccessInput(const SDL_Event* event);

	~CInputComponent();

};