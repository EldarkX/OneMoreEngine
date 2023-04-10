
#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"
#include "Modules/RenderModule/RenderManager.h"

#include "Modules/RenderModule/Shader.h"
#include "Modules/RenderModule/Texture.h"

void CSpriteComponent::BeginPlay()
{
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

		Texture->SetActive();

		Matrix4D world = scale * mOwner->GetActorTransform()->GetComputedTransform();

		shader->SetMatrixUniform("uWorldTransform", world);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

CSpriteComponent::~CSpriteComponent()
{
	GameEngine::GetGameEngine()->GetRenderManager()->RemoveDrawableComponent(this);
}
