#pragma once

#include "Component.h"

namespace sf
{
	class Drawable;
}

namespace ce
{
	class Transform;

	class DrawableComponent : public Component
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::DrawableComponent>(lua_State*);

		friend class DrawEventManager;

	public:
		DrawableComponent();
		~DrawableComponent();

		virtual sf::Drawable* GetDrawable() const;
		
		void SetDrawOrder(const int drawOrder);

		int GetDrawOrder() const;

		void SetGameObject(GameObject* gameObject);

	protected:
		int drawOrder;

		bool isNew;

		// The transform of this components GameObject
		ce::Transform* transform;

	private:
		// Binds parts of this script to Lua
		static void DoBind(lua_State* L);
	};
}