#include "ComponentRef.h"

#include "Component.h"
#include "Transform.h"
#include "Sprite.h"

#include <vector>

using ce::ComponentRef;

std::map<int, std::function<ce::Component(void)>> ce::ComponentRef::componentConstructMap;

int ce::ComponentRef::componentIDCounter = 0;

void ComponentRef()
{
	
}

void ce::ComponentRef::BindComponentID()
{
	std::vector<std::string> componentNames;

	componentNames.push_back("TransformID");
	//std::function<ce::Transform(void)> transformConstruct(&DoBind);
	//componentConstructMap.insert(std::make_pair(componentIDCounter++, transformConstruct));
}

void ce::ComponentRef::DoBind(lua_State * L)
{
}
