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

#include "MusicManager.h"

#include "LuaBind.h"

#include <SFML\Audio.hpp>

using namespace ce;

MusicManager::MusicManager() : 
    volume(1),
    music(new sf::Music())
{
}


MusicManager::~MusicManager()
{
}

void ce::MusicManager::PlayMusic(const std::string& fileName, bool loop)
{
	//Load the music file
	if (!music->openFromFile(fileName))
	{
        assert(false);
	}
	//Set the volume for the music
	music->setVolume(volume);
	//Play the music
	music->play();
}


//Setting the volume for the music
void ce::MusicManager::SetVolume(float volume)
{
	this->volume = volume;
}


//Get the volume for the music
float ce::MusicManager::GetVolume() const
{
	return volume;
}

void ce::MusicManager::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<MusicManager>("Music")
                .addConstructor<void(*)(void)>()
				.addFunction("PlayMusic", &MusicManager::PlayMusic)
				.addProperty("volume", &MusicManager::GetVolume, &MusicManager::SetVolume)
			.endClass()
		.endNamespace();
}
