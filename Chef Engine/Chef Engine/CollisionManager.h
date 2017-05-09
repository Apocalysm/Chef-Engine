#pragma once
#include <Box2D\Box2D.h>

namespace ce
{
	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();

		static b2World world;
	};
}
