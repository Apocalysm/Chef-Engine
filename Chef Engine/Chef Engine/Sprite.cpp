#include "Sprite.h"
#include "GameObject.h"
#include "DrawEventManager.h"

using ce::Sprite;

Sprite::Sprite()
{
	ce::DrawEventManager::AddSprite(this);

	// Gets the transform of the owner of this sprite-component
	transform = gameObject->GetTransform();
}

Sprite::Sprite(const std::string& fileName, const int newDrawOrder)
{
	// Gets the transform of the owner of this sprite-component
	transform = gameObject->GetTransform();

	//SetSprite(fileName);

	drawOrder = newDrawOrder;

	ce::DrawEventManager::AddSprite(this);
}

void Sprite::Update()
{
	// Updates psition, scale and rotation depending on the set values in the transform
	sprite->setPosition(transform->GetPosition() + position);
	sprite->setScale(transform->GetScale() + scale);
	sprite->setRotation(transform->GetRotation() + rotation);
}

void Sprite::SetSprite(const std::string& fileName)
{
	texture.loadFromFile(fileName);

	sprite->setTexture(texture);

	sprite->setPosition(transform->GetPosition());
}

void Sprite::SetPosition(const float x, const float y)
{
	position = sf::Vector2f(x, y);
}
void ce::Sprite::SetPosition(const sf::Vector2f newPosition)
{
	position = newPosition;
}

void Sprite::SetScale(const float x, const float y)
{
	//sprite.setScale(x, y);
	scale = sf::Vector2f(x, y);
}
void Sprite::SetScale(const sf::Vector2f newScale)
{
	//sprite.setScale(newScale);
	scale = newScale;
}

void Sprite::SetOrigin(const float x, const float y)
{
	sprite->setOrigin(x, y);
}
void Sprite::SetOrigin(const sf::Vector2f newOrigin)
{
	sprite->setOrigin(newOrigin);
}

void Sprite::SetRotation(const float angle)
{
	//sprite.setRotation(angle);
	rotation = angle;
}

void Sprite::SetColor(const sf::Color color)
{
	sprite->setColor(color);
}

void Sprite::SetColor(const int r, const int g, const int b, const int a)
{
	sprite->setColor(sf::Color(r, g, b, a));
}

void Sprite::SetDrawOrder(const int newDrawOrder)
{
	drawOrder = newDrawOrder;
}

sf::Sprite* Sprite::GetSprite() const
{
	return sprite;
}

sf::Vector2f Sprite::GetPosition() const
{
	return position;
}

sf::Vector2f Sprite::GetScale() const
{
	//return sprite.getScale();
	return scale;
}

sf::Vector2f Sprite::GetOrigin() const
{
	return sprite->getOrigin();
}

float Sprite::GetRotation() const
{
	//return sprite.getRotation();
	return rotation;
}

sf::Color Sprite::GetColor() const
{
	return sprite->getColor();
}

int Sprite::GetDrawOrder() const
{
	return drawOrder;
}

void Sprite::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<Sprite>("Sprite")
				.addConstructor<void(*)(void)>()
				.addProperty("sprite", &Sprite::GetSprite, &SetSprite)
				.addProperty("position", &Sprite::GetPosition, &Sprite::SetPosition)
				.addProperty("scale", &Sprite::GetScale, &Sprite::SetScale)
				.addProperty("rotation", &Sprite::GetRotation, &Sprite::SetRotation)
				.addProperty("origin", &Sprite::GetOrigin, &Sprite::SetOrigin)
				.addProperty("color", &Sprite::GetColor, &Sprite::SetColor)
				.addProperty("drawOrder", &Sprite::GetDrawOrder, &Sprite::SetDrawOrder)
			.endClass()
		.endNamespace();
}
