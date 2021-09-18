
#include "Modules/ObjectModule/Object/Actor/AnimSpriteActor.h"

#include "Modules/ObjectModule/Object/Actor/Components/AnimSpriteComponent.h"

#include "Modules/RenderModule/Texture.h"

AAnimSpriteActor::AAnimSpriteActor()
{
	mAnimSpriteComponent = AddComponent<CAnimSpriteComponent>();
}

Vector2D AAnimSpriteActor::GetActorSize() const
{
	if (mAnimSpriteComponent->GetTexture())
	{
		float X = mAnimSpriteComponent->GetTexture()->GetWidth() * GetActorScale().X();
		float Y = mAnimSpriteComponent->GetTexture()->GetHeight() * GetActorScale().Y();

		return Vector2D(X, Y);
	}
	return GetActorScale();
}

