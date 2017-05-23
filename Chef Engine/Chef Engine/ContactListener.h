#pragma once

#include <Box2D/Box2D.h>

namespace ce
{
	class ContactListener : public b2ContactListener
	{
	public:
		ContactListener();
		~ContactListener();

		// Is called when two colliders begin to touch
		void BeginContact(b2Contact* contact);

		// Is called when two colliders stops touching
		void EndContact(b2Contact* contact);
	};
}