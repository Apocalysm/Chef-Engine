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

#include "SoundManager.h"
#include "ResourceManager.h"
#include "LuaBind.h"

#include <SFML\Audio.hpp>

#include <assert.h>
#include <iostream>

using namespace ce;
float SoundManager::sfxMasterVolume = 1;

ce::SoundManager::SoundManager(std::string fileName) : sfxVolume(1)
{
	sounds.push_back(new sf::Sound());
	buffer = (ce::SoundBuffer*) ce::ResourceManager::GetResource(fileName);
	sounds[0]->setBuffer(*buffer->GetSoundBuffer());
}


ce::SoundManager::~SoundManager()
{

}



void ce::SoundManager::PlaySFX()
{
	//Setting the volume for the sound
	sfxVolume *= sfxMasterVolume;

	int location = -1;
	for (int i = 0; i < sounds.size(); i++)
	{
		//Check if the sound on position "i" is not playing
		if (sounds[i]->getStatus() != sf::Sound::Playing && location == -1)
		{
			location = i;
	}
}

	//Check if location is not equal to -1
	if (location != -1)
	{
		//Plays the sound again on the same location as the sound that stopped in the vector 
		sounds[location]->setBuffer(*buffer->GetSoundBuffer());
		sounds[location]->setVolume(sfxVolume);
		sounds[location]->play();
	}

	//IF not create a new sound in the vector
	else
{
		sf::Sound* newSound = new sf::Sound();

		newSound->setBuffer(*buffer->GetSoundBuffer());
		newSound->setVolume(sfxVolume);
		newSound->play();
		sounds.push_back(newSound);
	}
}

	
//Set the volume for THIS sound
void ce::SoundManager::SetSoundVolume(float volume)
{
	sfxVolume = volume;
}


//Get the volume for THIS sound
float ce::SoundManager::GetSoundVolume() const
{
	return sfxVolume;
}


//Setting the a volume for ALL the sounds
void ce::SoundManager::SetMasterVolume(float volume)
{
	sfxMasterVolume = volume;
}


//Getting the a volume for ALL the sounds
float ce::SoundManager::GetMasterVolume() const
{
	return sfxMasterVolume;

	/*for (auto i = 0; i < sounds.size(); i++)
	{
		if (sounds[i]->getStatus != sounds[i]->Playing)
{
			//buffer->DecrementUseCount();
		}
	}*/
}

void ce::SoundManager::DoBind(lua_State * L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Chef")
			.beginClass<SoundManager>("Sound")
				.addFunction("PlaySound", &SoundManager::PlaySFX)
				.addProperty("volume", &SoundManager::GetSoundVolume, &SoundManager::SetSoundVolume)
				.addProperty("masterVolume", &SoundManager::GetMasterVolume, &SoundManager::SetMasterVolume)
			.endClass()
		.endNamespace();
}


