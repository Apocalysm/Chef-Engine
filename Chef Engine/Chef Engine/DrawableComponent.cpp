#include "DrawableComponent.h"
#include "DrawEventManager.h"
#include "GameObject.h"

ce::DrawableComponent::DrawableComponent()
{
	isNew = true;

	drawOrder = 0;
}


ce::DrawableComponent::~DrawableComponent()
{
	ce::DrawEventManager::RemoveDrawable(this);
}


sf::Drawable* ce::DrawableComponent::GetDrawable() const
{
	return nullptr;
}


void ce::DrawableComponent::SetDrawOrder(const int drawOrder)
{
	ce::DrawEventManager::MoveDrawable(this, drawOrder);

	this->drawOrder = drawOrder;
}


int ce::DrawableComponent::GetDrawOrder() const
{
	return drawOrder;
}


void ce::DrawableComponent::SetGameObject(GameObject* gameObject)
{
	this->gameObject = gameObject;

	// Gets the transform of the owner of this sprite-component
	transform = gameObject->GetTransform();

	ce::DrawEventManager::AddDrawable(this);
}


void ce::DrawableComponent::DoBind(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<ce::DrawableComponent>("DrawableComponent")
				.addConstructor<void(*) (void)>()
				.addProperty("drawOrder", &DrawableComponent::GetDrawOrder, &DrawableComponent::SetDrawOrder)
			.endClass()
		.endNamespace();
}