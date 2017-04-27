#pragma once
#include "Component.h"
#include "Transform.h"

namespace ce
{
	class Sprite : public ce::Component
	{
	public:
		Sprite();
		Sprite(const std::string& fileName, const int drawOrder);

		void Update();

		void SetSprite(const std::string &fileName);

		void SetPosition(const float x, const float y);
		void SetPosition(const sf::Vector2f newPosition);

		void SetScale(const float x, const float y);
		void SetScale(const sf::Vector2f newScale);

		void SetOrigin(const float x, const float y);
		void SetOrigin(const sf::Vector2f newOrigin);

		void SetRotation(const float angle);

		void SetColor(const sf::Color color);
		void SetColor(const int r, const int g, const int b, const int a);

		void SetDrawOrder(const int drawOrder);

		sf::Sprite* GetSprite() const;

		sf::Vector2f GetPosition() const;

		sf::Vector2f GetScale() const;

		sf::Vector2f GetOrigin() const;

		float GetRotation() const;

		sf::Color GetColor() const;

		int GetDrawOrder() const;

	private:
		friend class DrawEventManager;
		sf::Sprite* sprite;
		sf::Texture texture;
		sf::Vector2f position;
		sf::Vector2f scale;
		float rotation;
		sf::Color color;
		int drawOrder = 0;
		bool isNew = true;

		// The transform of this components GameObject
		ce::Transform* transform; 

		// Bridges parts of this script to Lua
		static void DoBind(lua_State* L); 
	};
}

