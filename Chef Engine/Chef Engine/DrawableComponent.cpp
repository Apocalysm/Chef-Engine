#include "DrawableComponent.h"
#include "DrawEventManager.h"

sf::Drawable * ce::DrawableComponent::GetDrawable() const
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