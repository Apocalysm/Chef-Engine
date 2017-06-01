////////////////////////////////////////////////////////////
//
// Chef Engine
// Copyright (C) 2017 Oskar Svensson
//  
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////


#pragma once
#include "Common.h"
#include "LuaBridgeBinder.h"

struct lua_State;

namespace ce
{
	class GameObject;

    ////////////////////////////////////////////////////////////
    /// \brief Base class for all other Component classes
    ////////////////////////////////////////////////////////////
	class CHEF_API Component
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

