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
		~Sprite();

		void Update() override;


        #pragma region Position Methods
		void SetPosition(const float x, const float y);
		void SetPosition(const sf::Vector2f newPosition);

        sf::Vector2f GetPosition() const;
        #pragma endregion


        #pragma region Scale Methods
		void SetScale(const float x, const float y);
		void SetScale(const sf::Vector2f newScale);

		sf::Vector2f GetScale() const;
        #pragma endregion 


        #pragma region Rotation Methods
		void SetRotation(const float angle);
        
        float GetRotation() const;
        #pragma endregion 

        void SetOrigin(const float x, const float y);
		void SetOrigin(const sf::Vector2f newOrigin);
        
        sf::Vector2f GetOrigin() const;	

        void SetColor(const sf::Color color);
		void SetColor(const int r, const int g, const int b, const int a);
		
        sf::Color GetColor() const;

		void SetDrawOrder(const int drawOrder);
		
        int GetDrawOrder() const;
		
        void SetSprite(const std::string &fileName);

		sf::Sprite* GetSprite() const;

		void SetGameObject(GameObject* gameObject);

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