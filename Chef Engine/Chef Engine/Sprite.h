#pragma once
#include "Component.h"
#include "Transform.h"
#include "DrawEventManager.h"

namespace ce
{
	class Sprite : public ce::Component
	{
	public:
		Sprite();
		Sprite(const int drawOrder);
		~Sprite();

		void Update() override;

		#pragma region Origin Methods
        void SetOrigin(const float x, const float y);
		void SetOrigin(const sf::Vector2f newOrigin);
        
        sf::Vector2f GetOrigin() const;	
		#pragma endregion

		#pragma region Color Methods
        void SetColor(const sf::Color color);
		void SetColor(const int r, const int g, const int b, const int a);
		
        sf::Color GetColor() const;
		#pragma endregion

		void SetDrawOrder(const int drawOrder);
        int GetDrawOrder() const;
		
        void SetSprite(const std::string &fileName);
		void SetRealSprite(sf::Sprite* sprite); 

		sf::Sprite* GetSprite() const;

		void SetGameObject(GameObject* gameObject);

	private:
		friend class DrawEventManager;

		sf::Sprite* sprite;
		sf::Texture texture;

		sf::Color color;
		int drawOrder;
		bool isNew;

		// The transform of this components GameObject
		ce::Transform* transform;

		// Bridges parts of this script to Lua
		static void DoBind(lua_State* L); 
	};
}