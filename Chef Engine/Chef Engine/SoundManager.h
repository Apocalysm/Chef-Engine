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
#include "SoundBuffer.h"
#include "LuaBridgeBinder.h"

#include <string>

namespace sf
{
    class Music;
    class Sound;
}

namespace ce
{
    ////////////////////////////////////////////////////////////
    /// \brief This is the class you want to use when playing sounds
    /// Don't be fooled by the name SoundManager, in Lua it's actually
    /// just called Sound. You use the class by simply constructing it with
    /// the path of the sound file you want to use, and then using the PlaySound method
    /// 
    /// \code
    /// -- Creates a new sound and plays it
    /// 
    /// self.hitSound = Chef.Sound("Sounds\\hit.wav")
    /// self.hitSound:PlaySound()
    /// \endcode
    ///
    ////////////////////////////////////////////////////////////
	class SoundManager
	{
		friend void LuaBridgeBinder::Bind<ce::SoundManager>(lua_State*);

	public:
		SoundManager(const std::string& fileName);
		~SoundManager();


		void PlaySFX();
		void SetSoundVolume(float volume);
		float GetSoundVolume() const;

		void SetMasterVolume(float volume);
		float GetMasterVolume() const;

	private:
		static void DoBind(lua_State* L);

		std::vector<sf::Sound*> sounds;
		std::string fileName;
		ce::SoundBuffer* buffer;

        ////////////////////////////////////////////////////////////
        /// \brief Global volume of all sound clips
        /// The individual volume of all sound clips is multiplied by this value
        /// \code
        /// -- Sets the global volume to be higher of all sounds
        /// 
        /// Chef.Sound.masterVolume = 1.5
        /// \endcode
        ////////////////////////////////////////////////////////////
		static float sfxMasterVolume;

        ////////////////////////////////////////////////////////////
        /// \brief Volume of the individual sound-file
        /// The max volume of a sound is 2 
        /// \code
        /// -- Sets the volume to be higher of the sound
        /// 
        /// self.sound = Chef.Sound("Sounds\\hit.wav")
        /// self.sound.volume = self.sound.volume * 0.5
        /// \endcode
        ////////////////////////////////////////////////////////////
		float sfxVolume;

	};
}