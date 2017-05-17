#pragma once
#include "Component.h"

namespace ce
{
	class Camera: public ce::Component
	{
	public:
		Camera();
		~Camera();

		void SetSize(const sf::Vector2f &size);
		sf::Vector2f GetSize() const;


		void SetCenter(const sf::Vector2f & center);
		sf::Vector2f GetCenter() const;
		void Move(const sf::Vector2f &offset);

		bool GetFollow() const;
		void SetFollow(const bool &follow);

		sf::View GetView() const;

		void Update();

	private:
		sf::View view;

		sf::Vector2f size;
		sf::Vector2f center;	
		sf::Vector2f worldBounce;

		bool follow;
		
	};
}
