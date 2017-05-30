#include "GameObject.h"

#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Camera.h"
#include "Text.h"

#include "GameObjectManager.h"
#include "DrawEventManager.h"


//using GameObject;
namespace ce
{
    const int GameObject::LAYER_AMOUNT = 6;

    // Initializes our ID generator
    unsigned long long GameObject::uniqueIDCounter = 0;

    GameObject::GameObject()
        : GameObject("none")
    {
    }

    GameObject::GameObject(std::string name)
    {
        // Sets the instanceID of the object to the incremented value of uniqueIDCounter
        instanceID = uniqueIDCounter++;

        // The object was instantiated this frame
        isNew = true;

        transform = AddComponent<Transform>();

        GameObjectManager::AddObject(this);

        this->name = name;

        this->active = true;

        layer = Default;
    }


    GameObject::~GameObject()
    {
    }


    void GameObject::SetActive(bool active)
    {
        this->active = active;
    }


    bool GameObject::GetActive() const
    {
        return this->active;
    }


    void GameObject::SetLayer(Layers newLayer)
    {
    }


    int GameObject::GetLayer() const
    {
        return layer;
    }


    void GameObject::SetTransform(Transform* transform)
    {
        this->transform = transform;
    }


    Transform* GameObject::GetTransform() const
    {
        return transform;
    }


    unsigned long long GameObject::GetID() const
    {
        return instanceID;
    }


    bool GameObject::operator==(const GameObject & other)
    {
        if (instanceID == other.instanceID)
        {
            // This is the same gameobject
            return true;
        }
        return false;
    }


    // Runs the Start method once on all the new Components
    void GameObject::ComponentStart()
    {
        // Iterates through all of the components this GameObject is holding
        // and calls the Start method on them
        for (auto it = components.begin(); it != components.end(); it++)
        {
            // We also check if the Component is tagged as 'new' so we know it's the first time it's run
            if (it->second->isNew && it->second->enabled)
            {
                it->second->Start();
                it->second->isNew = false;
            }
        }
        // Does the same thing for luaComponents
        for (auto it = luaComponents.begin(); it != luaComponents.end(); it++)
        {                     
            if (it->second->isNew && it->second->enabled)
            {
                it->second->Start();
                it->second->isNew = false;
            }
        }
    }

    // Runs the Update method each frame on all of the Components this GameObject is holding
    void GameObject::ComponentUpdate()
    {
        // Iterates through all of the lua-components this GameObject is holding
        // and calls the Update method on them
        for (auto it = luaComponents.begin(); it != luaComponents.end(); it++)
        {
            if (it->second->GetEnabled())
            {
                it->second->Update();
            }
        }
        // Does the same thing for the normal components
        for (auto it = components.begin(); it != components.end(); it++)
		{
            if (it->second->GetEnabled())
			{
                it->second->Update();
            }
        }
    }

    // Getter and setter methods for 'name' variable
    std::string GameObject::GetName() const
    {
        return name;
    }


    void GameObject::SetName(std::string name)
    {
        this->name = name;
    }


    // Getter and setter methods for 'tag' variable
    std::string GameObject::GetTag() const
    {
        return tag;
    }


    void GameObject::SetTag(std::string tag)
    {
        this->tag = tag;
    }


void GameObject::Destroy()
{
	// Iterates all of GameObject's components
	for (auto it = components.begin(); it != components.end(); it++)
	{
		// Deletes the component from the vector and the memory
        delete it->second;
	}
    components.clear();

	ce::GameObjectManager::RemoveObject(this);

	delete this;
}

// Creates a new LuaComponent and adds it to this GameObject
luabridge::LuaRef GameObject::AddLuaComponent(luabridge::LuaRef ref)
{
    if (!ref.isTable())
    {
        std::cerr << lua_tostring(ref.state(), -1) << std::endl;
        assert(false);
    }
    // Checks if the ref has a variable "ID"
    if (!ref["ID"].isNumber())
    {
        std::cerr << lua_tostring(ref.state(), -1) << std::endl;
        assert(false);
    }

    int id = ref["ID"];
         
    if (luaComponents.find(id) == luaComponents.end())
    {
        // Creates a new LuaComponent with the ref we passed as an argument
        LuaComponent* newComponent = new ce::LuaComponent(ref);

        // Sets the component's gameObject reference
        newComponent->SetGameObject(this);

        // Passes this GameObject and the new luaComponent back to our new component instance in Lua
        luabridge::LuaRef newRef = ref["Create"](newComponent);

        // Sets the LuaComponent's ref to the newly created one
        newComponent->ref = newRef;

        // Adds the new Lua Component to this GameObject
        luaComponents.insert(std::make_pair(id, newComponent));

        // Sends the newRef back into Lua
        return newRef;
    }
    std::cerr << "You sadly can't add the same component type twice to a GameObject. Yet..." << std::endl;
    assert(false);
}

    
    // Gets a LuaComponent and returns that components specified LuaRef
    luabridge::LuaRef GameObject::GetLuaComponent(int ID)
    {
        // Checks if there is an element on index "ID" 
        if (luaComponents[ID]->ref.isTable())
        {
            return luaComponents[ID]->ref;
        }
    }

    // Removes LuaComponent from the luaComponents map
    void GameObject::RemoveLuaComponent(int ID)
    {
        // Checks if there is an element on index "ID" 
        if (luaComponents[ID])
        {                    
            delete luaComponents[ID];
        
            luaComponents.erase(ID);
        }
    }

void GameObject::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")

		.beginClass<GameObject>("GameObject")
		.addConstructor<void(*) (std::string)>()

		.addProperty("active", &GameObject::GetActive, &GameObject::SetActive)
		.addProperty("layer", &GameObject::GetLayer, &GameObject::SetLayer)
		.addProperty("instanceID", &GameObject::GetID)
		.addProperty("name", &GameObject::GetName, &GameObject::SetName)
		.addProperty("transform", &GameObject::GetTransform)
		.addFunction("Equals", &GameObject::operator==)

		.addFunction("AddLuaComponent", &GameObject::AddLuaComponent)
		.addFunction("GetLuaComponent", &GameObject::GetLuaComponent)
		.addFunction("RemoveLuaComponent", &GameObject::RemoveLuaComponent)

		.addFunction("GetTransform", &GameObject::GetComponent<ce::Transform>)

		.addFunction("AddSprite", &GameObject::AddComponent<ce::Sprite>)
		.addFunction("GetSprite", &GameObject::GetComponent<ce::Sprite>)
		.addFunction("RemoveSprite", &GameObject::RemoveComponent<ce::Sprite>)

		.addFunction("AddCollider", &GameObject::AddComponent<ce::Collider>)
		.addFunction("GetCollider", &GameObject::GetComponent<ce::Collider>)
		.addFunction("RemoveCollider", &GameObject::RemoveComponent<ce::Collider>)

		.addFunction("AddCamera", &GameObject::AddComponent<ce::Camera>)
		.addFunction("GetCamera", &GameObject::GetComponent<ce::Camera>)
		.addFunction("RemoveCamera", &GameObject::RemoveComponent<ce::Camera>)

		.addFunction("AddText", &GameObject::AddComponent<ce::Text>)
		.addFunction("GetText", &GameObject::GetComponent<ce::Text>)
		.addFunction("RemoveText", &GameObject::RemoveComponent<ce::Text>)

                /*.addStaticData("Default", Default, false)
                .addStaticData("Player", Player, false)
                .addStaticData("Enemy", Enemy, false)
                .addStaticData("Terrain", Terrain, false)
                .addStaticData("UI", UI, false)*/

                .endClass()
            .endNamespace();
    }
}