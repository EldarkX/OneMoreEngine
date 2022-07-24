#pragma once

#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

class OTexture;

class CSpriteComponent : public CTransform2DComponent
{
	friend class	RenderManager;

public:

	virtual void			BeginPlay() override;

	OTexture*				GetTexture() const { return Texture; }
	void					SetTexture(OTexture* newTexture);
	
	int						GetDrawOrder() const { return DrawOrder; }
	void					SetDrawOrder(int newDrawOrder) { DrawOrder = newDrawOrder; }

							~CSpriteComponent();

protected:

	virtual void			Draw(class Shader* shader);

	int						DrawOrder = 100;

	OTexture*				Texture = nullptr;

};