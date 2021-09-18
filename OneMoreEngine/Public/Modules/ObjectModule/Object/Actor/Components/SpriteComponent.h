#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class Texture;

class CSpriteComponent : public CBaseComponent
{
	friend class	RenderManager;

public:

	virtual void	BeginPlay() override;

	Texture			*GetTexture() const { return mTexture; }
	void			SetTexture(Texture* newTexture);
	
	int				GetDrawOrder() const { return mDrawOrder; }
	void			SetDrawOrder(int newDrawOrder) { mDrawOrder = newDrawOrder; }

	~CSpriteComponent();

protected:

	virtual void	Draw(class Shader* shader);

	int				mDrawOrder = 100;

	Texture			*mTexture = nullptr;

};