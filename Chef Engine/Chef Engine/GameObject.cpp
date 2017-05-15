#include "GameObject.h"

#include "Component.h"
#include "Sprite.h"
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

        this->active = true;

        layer = Default;

        // Adds references to the Layers we can add to Lua
        // { Default, Player, Enemy, Terrain, UI}
        layerRef.push_back(Default);
        layerRef.push_back(Player);
        layerRef.push_back(Enemy);
        layerRef.push_back(Terrain);
        layerRef.push_back(UI);

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
            if (it->second->GetIsNew() && it->second->GetEnabled())
            {
                it->second->Start();
                it->second->SetIsNew(false);
            }
        }
    }

    // Runs the Update method each frame on all of the Components this GameObject is holding
    void GameObject::ComponentUpdate()
    {
        // Iterates through all of the components this GameObject is holding
        // and calls the Update method on them
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
        Sprite* spr = GetComponentInternal<Sprite>();

        if (spr != nullptr)
        {
            DrawEventManager::RemoveSprite(spr);
            //delete GetComponent<Sprite>()->;
        }

        // Iterates all of GameObject's components
        for (auto it = components.begin(); it != components.end(); it++)
        {
            // Deletes the component from the vector and the memory
            delete it->second;
        }
        components.clear();

        GameObjectManager::RemoveObject(this);
    }
    
    
    LuaComponent* GameObject::AddLuaComponent(lua_State* L, const std::string* scriptPath, const std::string* tableName)
    {
        LuaComponent* newComponent = AddComponent<LuaComponent>();
        newComponent->LoadScript(L, scriptPath, tableName);

        return newComponent;
    }

    void GameObject::DoBind(lua_State * L)
    {
        luabridge::getGlobalNamespace(L)
            .beginNamespace("Chef")
                .beginClass<GameObject>("GameObject")
                    .addProperty("active", &GameObject::GetActive, &GameObject::SetActive)
                    .addProperty("layer", &GameObject::GetLayer, &GameObject::SetLayer)
                    .addProperty("instanceID", &GameObject::GetID)
                    .addFunction("AddComponent", &GameObject::AddComponent)
                    .addFunction("AddLuaComponent", )
                    .addFunction("GetComponent", &GameObject::GetComponent)
                    .addFunction("RemoveComponent", &GameObject::RemoveComponent)           
                    /*.addData("Default", &GameObject::layerRef[0], false)
                    .addData("Player", &GameObject::layerRef[1], false)
                    .addData("Enemy", &GameObject::layerRef[2], false)
                    .addData("Terrain", &GameObject::layerRef[3], false)
                    .addData("UI", &GameObject::layerRef[4], false)*/
                .endClass()
            .endNamespace();
    }
}