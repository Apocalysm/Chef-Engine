#pragma once
#include "Component.h"
#include "LuaBridgeBinder.h"

namespace ce
{
	class Camera: public ce::Component
	{
		friend void LuaBridgeBinder::Bind<ce::Camera>(lua_State*);

	public:
		Camera();
		~Camera();

		void SetSize(const sf::Vector2f &size);
		sf::Vector2f GetSize() const;

		void SetZoom(float zoom);
		float GetZoom() const;

		void SetCenter(const sf::Vector2f & center);
		sf::Vector2f GetCenter() const;

		bool GetFollow() const;
		void SetFollow(const bool &follow);

		sf::View GetView() const;

		void Update();

	private:
		static void DoBind(lua_State* L);
		sf::View view;
		sf::Vector2f size;
		sf::Vector2f center;	
		sf::Vector2f worldBounce;
		sf::Vector2i mapSize;

		bool follow;
		float zoom = 1;
	};
}
