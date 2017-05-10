//-----------------------------------------------------------------------------
// TmxColor.h
//
// Copyright (c) 2017, Håkan Levin Henriksson
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TAMIR ATIAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Håkan Levin Henriksson
//-----------------------------------------------------------------------------
#pragma once

#include <string>

// typedef for a byte, until C++17 adds std::byte
typedef unsigned char byte;

namespace Tmx
{
	//-------------------------------------------------------------------------
	// A class used for storing information about a color.
	//-------------------------------------------------------------------------
	class Color
	{
	public:
		Color();
		Color(const std::string& col);
		Color(const unsigned long& col);
		Color(const byte& red, const byte& green, const byte& blue, const byte& alpha = 255);
		~Color();

		void SetColor(const std::string& col);
		void SetColor(const unsigned long& col);
		void SetColor(const byte& red, const byte& green, const byte& blue, const byte& alpha = 255);

		const byte GetAlpha() const;
		const byte GetRed() const;
		const byte GetGreen() const;
		const byte GetBlue() const;


	private:
		unsigned long color;
	};
}