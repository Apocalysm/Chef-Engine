#pragma once
#include "LuaBridgeBinder.h"

#include <SFML\Graphics.hpp>

namespace ce
{
	class GameObject;

    ////////////////////////////////////////////////////////////
    /// \brief Base class for all other Component classes
    ////////////////////////////////////////////////////////////
	class Component
	{
		// Befriends the templated Bind function so it can access our protected functions
		friend void LuaBridgeBinder::Bind<ce::Component>(lua_State*);

	public:
		Component();
		virtual ~Component();

        
        /// \brief Start is called on the frame when a script is enabled just before the Update method is Called for the first time.
		virtual void Start();
		
        /// \brief Update is called every frame
        virtual void Update();

		// Getter for the 'ID'-variable
		int GetID() const;
		void SetID(int ID);

		// Getter and setter for the 'enabled'-variable
		void SetEnabled(bool enabled);
		bool GetEnabled() const;
        
        void SetIsNew(bool isNew);
        bool GetIsNew() const;

		// Getter for 'gameObject'-variable
		GameObject* GetGameObject() const;
		virtual void SetGameObject(GameObject* gameObject);

		bool operator==(const Component& other);

	protected:
		// The GameObject holding this Component
		ce::GameObject* gameObject;

	private: 
        friend class GameObject;

		// The ID of the Component, is set in AddComponent
		int ID;

        // If we just created the Component
        bool isNew;

		// This decides if the Component should be updated for example via the Update method
        /// \brief Enabled Components are updated, disabled Components are not.
        bool enabled;
		
        static void DoBind(lua_State* L);

	};
}

