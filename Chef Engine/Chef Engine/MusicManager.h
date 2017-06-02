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
#include "LuaBridgeBinder.h"

#include <string>

namespace sf
{
	class Music;
}

namespace ce
{
    ////////////////////////////////////////////////////////////
    /// \brief This is the class you want to use when playing music
    /// Don't be fooled by the name MusicManager, in Lua it's actually
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
	class MusicManager
	{
		friend void LuaBridgeBinder::Bind<ce::MusicManager>(lua_State*);
	public:
		MusicManager() = delete;

        ////////////////////////////////////////////////////////////
        /// \brief Starts to play the specified sound-file
        /// You can choose to loop the music piece and then it will loop indefinetely
        /// \code
        /// -- Plays the music piece
        /// 
        /// self.music = Chef.Music()
        /// self.music:PlayMusic("Sounds\\platformer_music_happy.flac")
        /// \endcode
        ////////////////////////////////////////////////////////////
		static void PlayMusic(const std::string& fileName, bool loop);
		static void SetVolume(float volume);
		static float GetVolume();

	private:
        static sf::Music* music;

		static void DoBind(lua_State* L);

        ////////////////////////////////////////////////////////////
        /// \brief Volume of the music
        /// The max volume is 2 
        /// \code
        /// -- Sets the volume to be higher of the music
        /// 
        /// self.music = Chef.Music()
        /// self.music.volume = 0.5
        /// self.music:PlayMusic("Sounds\\Beautiful_String_Concert.flac")
        /// \endcode
        ////////////////////////////////////////////////////////////
		static float volume;
	};
}

