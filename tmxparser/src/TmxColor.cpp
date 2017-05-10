//-----------------------------------------------------------------------------
// TmxColor.cpp
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

#include "TmxColor.h"

namespace Tmx
{
	Color::Color()
		: color(0)
	{
	}

	Color::Color(const std::string& col)
	{
		SetColor(col);
	}

	Color::Color(const unsigned long& col)
	{
		SetColor(col);
	}

	Color::Color(const byte& red, const byte& green, const byte& blue, const byte& alpha)
	{
		SetColor(red, green, blue, alpha);
	}

	Color::~Color()
	{}

	void Color::SetColor(const std::string& col)
	{
		color = std::stoul(col, nullptr, 16);
	}

	void Color::SetColor(const unsigned long& col)
	{
		color = col;
	}

	void Color::SetColor(const byte& red, const byte& green, const byte& blue, const byte& alpha)
	{
		color = ((alpha << 24) +
				 (red << 16) +
				 (green << 8) +
				 (blue));
	}

	const byte Color::GetAlpha() const
	{
		return (color & 0xFF000000) >> 24;
	}

	const byte Color::GetRed() const
	{
		return (color & 0x00FF0000) >> 16;
	}

	const byte Color::GetGreen() const
	{
		return (color & 0x0000FF00) >> 8;
	}

	const byte Color::GetBlue() const
	{
		return (color & 0x000000FF);
	}
}