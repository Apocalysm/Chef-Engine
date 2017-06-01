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
#include <vector>
#include <map>

namespace sf
{
    class Sprite;
    class RenderStates;
    class RenderWindow;
}

namespace ce
{
	class DrawableComponent;
    class TileMapLayer;
	class Sprite;

	class DrawEventManager
	{
	public:
        CHEF_API DrawEventManager();
        static void AddDrawable(DrawableComponent* drawable);
		static void RemoveDrawable(DrawableComponent* drawable);
        static void MoveDrawable(DrawableComponent* drawable, int newDrawOrder);
		static void AddTmxLayers(std::vector<std::map<int, ce::TileMapLayer*>> tileMapLayers);
        CHEF_API void Draw(sf::RenderWindow& window);

	private:
        typedef unsigned long long uint64;

		typedef std::map<uint64, DrawableComponent*> DrawableMap;
		typedef std::map<uint64, DrawableMap> OrderDrawableMap;

		// OrderDrawableMap with DrawableComponents recently created
		static OrderDrawableMap enumToMapNewDrawable;

		// Map with DrawableComponents
		static OrderDrawableMap enumToMapDrawable;

		// Vector containing layers from Tiled to be drawn
        static std::vector<std::map<int, ce::TileMapLayer*>> tileMapLayers;
		
        static std::vector<sf::RenderStates> renderStates;
	};
}