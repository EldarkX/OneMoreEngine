#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"
#include "Modules/RenderModule/RenderManager.h"

#include "Modules/RenderModule/Shader.h"
#include "Modules/RenderModule/Texture.h"

void CSpriteComponent::BeginPlay()
{
	CTransform2DComponent::BeginPlay();

	GameEngine::GetGameEngine()->GetRenderManager()->AddDrawableComponent(this);
}

void CSpriteComponent::SetTexture(OTexture* newTexture)
{
	Texture = newTexture;
}

void CSpriteComponent::Draw(Shader* shader)
{
	if (GetTexture())
	{
		Matrix4D scale = Matrix4D::OneMatrix();
		scale(0, 0) = static_cast<float>(GetTexture()->GetWidth());
		scale(1, 1) = static_cast<float>(GetTexture()->GetHeight());

		if (Texture)
			Texture->SetActive();

		Matrix4D world = scale * GetComputedWorldTransform();

		shader->SetMatrixUniform("uWorldTransform", world);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

CSpriteComponent::~CSpriteComponent()
{
	GameEngine::GetGameEngine()->GetRenderManager()->RemoveDrawableComponent(this);
}
