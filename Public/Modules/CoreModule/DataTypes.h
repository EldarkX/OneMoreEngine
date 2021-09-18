#pragma once

enum class ECollisionChannel
{
	CCE_StaticObject1,
	CCE_StaticObject2,
	CCE_StaticObject3,
	CCE_DynamicObject1,
	CCE_DynamicObject2,
	CCE_DynamicObject3,
	CCE_Player
};

enum class ECollisionType
{
	CTE_Ignore,
	CTE_Collide
};

enum class EGameStatus
{
	GSE_Game,
	GSE_Pause,
	GSE_Exit
};