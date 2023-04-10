
#include "Modules/ObjectModule/Object/Actor/SpriteActor.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include "Modules/RenderModule/Texture.h"

ASpriteActor::ASpriteActor()
{
	mSpriteComponent = AddComponent<CSpriteComponent>();
}

Vector2D ASpriteActor::GetActorSize() const
{
	if (mSpriteComponent->GetTexture())
		return Vector2D(mSpriteComponent->GetTexture()->GetWidth() * GetActorScale().X(), mSpriteComponent->GetTexture()->GetHeight() * GetActorScale().Y());
	return GetActorScale();
}
