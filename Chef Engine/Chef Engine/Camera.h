#pragma once
#include "Component.h"
#include "LuaBridgeBinder.h"

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
		Camera();
		~Camera();

    

        // The main camera, the camera that's currently in use
        static Camera* main;
        // The window of the game
        static sf::RenderWindow* window;

		void SetSize(const sf::Vector2f &size);
		sf::Vector2f GetSize() const;

		void SetZoom(float zoom);
		float GetZoom() const;

		void SetCenter(const sf::Vector2f & center);
		sf::Vector2f GetCenter() const;

		bool GetFollow() const;
		void SetFollow(const bool &follow);

		sf::View GetView() const;
        
        void UpdateCamera();

	private:
		static void DoBind(lua_State* L);

		sf::View view;

        ////////////////////////////////////////////////////////////
        /// \brief How big the camera's viewport is
        /// \code
        /// -- The Camera's viewport is now 128x128
        /// 
        /// camera.size = Chef.Vector2f(128, 128)
        /// \endcode
        ////////////////////////////////////////////////////////////
		sf::Vector2f size;

        ////////////////////////////////////////////////////////////
        /// \brief The position the Camera looks at
        /// \code
        /// -- The Camera is set to look at position (5, 100)
        /// 
        /// camera.center = Chef.Vector2f(5, 100)
        /// \endcode
        ////////////////////////////////////////////////////////////
		sf::Vector2f center;

		sf::Vector2f worldBounce;
		sf::Vector2i mapSize;

        /// \brief If the Camera should follow the GameObject is on
		bool follow;

        /// \brief Resize the view rectangle relatively to its current size. 
        float zoom;
	};
}
