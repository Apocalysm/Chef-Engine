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

namespace sf
{
    class Texture;
    class VertexArray;
}

namespace ce
{
	class TileMapLayer
	{
		public:
			TileMapLayer(sf::VertexArray* va, const sf::Texture& txt);
			~TileMapLayer();

			sf::VertexArray& GetVertexArray();
			void SetVertexArray(sf::VertexArray& vertexArray);

			const sf::Texture& GetTexture() const;
			void SetTexture(const sf::Texture& texture);

		private:
			sf::VertexArray* vertexArray;
			const sf::Texture* texture;
	};
}

