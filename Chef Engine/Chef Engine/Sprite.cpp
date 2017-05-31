#include "Sprite.h"
#include "GameObject.h"
#include "DrawEventManager.h"
#include "ResourceManager.h"

using ce::Sprite;

Sprite::Sprite()
{
	sprite = new sf::Sprite();
}


Sprite::Sprite(const int newDrawOrder)
{
	sprite = new sf::Sprite();

	drawOrder = newDrawOrder;
}


Sprite::~Sprite()
{
	delete sprite;

	texture->DecrementUseCount();
}


void Sprite::Update()
{
	// Updates psition, scale and rotation depending on the set values in the transform
	sprite->setPosition(transform->GetPosition());
	sprite->setRotation(transform->GetRotation());
	sprite->setScale(transform->GetScale());
}


void Sprite::SetSprite(const std::string& fileName)
{
	texture = (ce::Texture*)ce::ResourceManager::GetResource(fileName);

	sprite->setTexture(*texture->GetTexture());

	sprite->setPosition(transform->GetPosition());
}

void ce::Sprite::ChangeSprite(sf::Sprite* sprite)
{
	delete this->sprite; 
	this->sprite = sprite;
}


void Sprite::SetOrigin(const float x, const float y)
{
	sprite->setOrigin(x, y);
}


void Sprite::SetOrigin(const sf::Vector2f newOrigin)
{
	sprite->setOrigin(newOrigin);
}


void Sprite::SetColor(const sf::Color& color)
{
	sprite->setColor(color);
}


void Sprite::SetColor(const int r, const int g, const int b, const int a)
{
	sprite->setColor(sf::Color(r, g, b, a));
}


sf::Sprite* Sprite::GetSprite() const
{
	return sprite;
}


sf::Drawable* ce::Sprite::GetDrawable() const
{
	return sprite;
}


sf::Vector2f Sprite::GetOrigin() const
{
	return sprite->getOrigin();
}


sf::Color Sprite::GetColor() const
{
	return sprite->getColor();
}


void Sprite::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.deriveClass<Sprite, Component>("Sprite")
				.addConstructor<void(*)(void)>()
                .addFunction("SetSprite", &Sprite::SetSprite)
				.addProperty("sprite", &Sprite::GetSprite, &Sprite::ChangeSprite)
				.addProperty("origin", &Sprite::GetOrigin, &Sprite::SetOrigin)
				.addProperty("color", &Sprite::GetColor, &Sprite::SetColor)
				.addProperty("drawOrder", &Sprite::GetDrawOrder, &Sprite::SetDrawOrder)
			.endClass()
		.endNamespace();
}