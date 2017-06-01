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

////////////////////////////////////////////////////////////
//
// Author: Rasmus Andersson
//
////////////////////////////////////////////////////////////

#pragma once
#include "Common.h"
#include "Component.h"
#include "Vec2.h"
#include "LuaBridgeBinder.h"

namespace sf
{
    class RenderWindow;
    class View;
}

struct lua_State;

namespace ce
{
    ////////////////////////////////////////////////////////////
    /// \brief Component that can view a specified view of the window
    /// Add a Camera to a GameObject with GameObject:AddCamera()
    /// \code
    /// --Creates a GameObject and adds a Camera to it
    ///
    /// object = Chef.GameObject("name")
    ///
    /// camera = object:AddCamera() 
    /// \endcode
    /// 
    /// \n Tries to get a Camera from a GameObject with GameObject:GetCamera()
    /// \code
    /// --Gets a Camera from the GameObject "object"
    ///
    /// camera = object:GetCamera()
    /// \endcode
    ///
    /// \n Remove a Camera from a GameObject with GameObject:RemoveCamera()
    /// \code
    /// --Tries to remove a Camera from the GameObject "object"
    ///
    /// object:RemoveCamera()
    /// \endcode
    ////////////////////////////////////////////////////////////
	class Camera: public ce::Component
	{
		friend void LuaBridgeBinder::Bind<ce::Camera>(lua_State*);

	public:
        ////////////////////////////////////////////////////////////
        /// \brief Default Camera Constructor.
        /// In Lua you use GameObject:AddCamera()
        /// \code
        /// --Creates a GameObject and adds a Camera to it
        ///
        /// object = Chef.GameObject("name")
        ///
        /// camera = object:AddCamera()
        /// \endcode
        ////////////////////////////////////////////////////////////
		CHEF_API Camera();
		CHEF_API ~Camera();

    

        // The main camera, the camera that's currently in use
        CHEF_API static Camera* main;
        // The window of the game
        CHEF_API static sf::RenderWindow* window;

		void SetSize(const ce::Vec2f& size);
		const ce::Vec2f& GetSize() const;

		void SetZoom(float zoom);
		float GetZoom() const;

		void SetCenter(const ce::Vec2f& center);
        const ce::Vec2f& GetCenter() const;

		bool GetFollow() const;
		void SetFollow(const bool &follow);

		const sf::View* GetView() const;
        
        CHEF_API void UpdateCamera();

	private:
		static void DoBind(lua_State* L);

		sf::View* view;

        ////////////////////////////////////////////////////////////
        /// \brief How big the camera's viewport is
        /// \code
        /// -- The Camera's viewport is now 128x128
        /// 
        /// camera.size = Chef.Vector2f(128, 128)
        /// \endcode
        ////////////////////////////////////////////////////////////
		ce::Vec2f size;

        ////////////////////////////////////////////////////////////
        /// \brief The position the Camera looks at
        /// \code
        /// -- The Camera is set to look at position (5, 100)
        /// 
        /// camera.center = Chef.Vector2f(5, 100)
        /// \endcode
        ////////////////////////////////////////////////////////////
        ce::Vec2f center;

        ce::Vec2f worldBounce;
        ce::Vec2i mapSize;

        /// \brief If the Camera should follow the GameObject is on
		bool follow;

        /// \brief Resize the view rectangle relatively to its current size. 
        float zoom;
	};
}
