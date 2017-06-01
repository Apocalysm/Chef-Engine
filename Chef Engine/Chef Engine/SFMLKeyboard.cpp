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


#include "SFMLKeyboard.h"

#include "LuaBind.h"

#include <SFML\Window\Keyboard.hpp>

using ce::SFMLKeyboard;

char* ce::SFMLKeyboard::keys = 0;
char* ce::SFMLKeyboard::newKeys = 0;
SFMLKeyboard::SFMLKeyboard()
{
}


SFMLKeyboard::~SFMLKeyboard()
{
}


void ce::SFMLKeyboard::Initialize()
{
	newKeys = new char[sf::Keyboard::KeyCount];
	keys = new char[sf::Keyboard::KeyCount];
	for (auto i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		newKeys[i] = 1;
		keys[i] = 1;
	}
}


void ce::SFMLKeyboard::SetKeyDown(int key)
{
	newKeys[key] = 2;
	keys[key] = 2;
}


void ce::SFMLKeyboard::SetKeyUp(int key)
{
	newKeys[key] = 0;
	keys[key] = 0;
}


bool ce::SFMLKeyboard::GetKey(int key)
{
	return keys[sf::Keyboard::Key(key)] == 2;
}


bool ce::SFMLKeyboard::GetKeyDown(int key)
{
    return newKeys[sf::Keyboard::Key(key)] == 2;
}


bool ce::SFMLKeyboard::GetKeyUp(int key)
{
	//If the current key is 0 that means its released and we can return true
	if (newKeys[sf::Keyboard::Key(key)] == 0)
	{
		return true;
	}

	return false;
}


void ce::SFMLKeyboard::ResetKeyboard()
{
	memset(newKeys, 1, sf::Keyboard::KeyCount);
	memset(keys, 1, sf::Keyboard::KeyCount);

}


void ce::SFMLKeyboard::ClearKeys()
{
	for (size_t i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		newKeys[i] = 1;
	}
}


#pragma region Keyboard definitions
int A = sf::Keyboard::A;
int B = sf::Keyboard::B;
int C = sf::Keyboard::C;
int D = sf::Keyboard::D;
int E = sf::Keyboard::E;
int F = sf::Keyboard::F;
int G = sf::Keyboard::G;
int H = sf::Keyboard::H;
int I = sf::Keyboard::I;
int J = sf::Keyboard::J;
int K = sf::Keyboard::K;
int L = sf::Keyboard::L;
int M = sf::Keyboard::M;
int N = sf::Keyboard::N;
int O = sf::Keyboard::O;
int P = sf::Keyboard::P;
int Q = sf::Keyboard::Q;
int R = sf::Keyboard::R;
int S = sf::Keyboard::S;
int T = sf::Keyboard::T;
int U = sf::Keyboard::U;
int V = sf::Keyboard::V;
int W = sf::Keyboard::W;
int X = sf::Keyboard::X;
int Y = sf::Keyboard::Y;
int Z = sf::Keyboard::Z;
int Num0 = sf::Keyboard::Num0;
int Num1 = sf::Keyboard::Num1;
int Num2 = sf::Keyboard::Num2;
int Num3 = sf::Keyboard::Num3;
int Num4 = sf::Keyboard::Num4;
int Num5 = sf::Keyboard::Num5;
int Num6 = sf::Keyboard::Num6;
int Num7 = sf::Keyboard::Num7;
int Num8 = sf::Keyboard::Num8;
int Num9 = sf::Keyboard::Num9;
//int Escape = sf::Keyboard::Escape;
int LControl = sf::Keyboard::LControl;
int LShift = sf::Keyboard::LShift;
int LAlt = sf::Keyboard::LAlt;
int LSystem = sf::Keyboard::LSystem;
int RControl = sf::Keyboard::RControl;
int RShift = sf::Keyboard::RShift;
int RAlt = sf::Keyboard::RAlt;
int RSystem = sf::Keyboard::RSystem;
int RBracket = sf::Keyboard::RBracket;
int LBracket = sf::Keyboard::LBracket;
int Menu = sf::Keyboard::Menu;
int SemiColon = sf::Keyboard::SemiColon;
int Comma = sf::Keyboard::Comma;
int Period = sf::Keyboard::Period;
int Quote = sf::Keyboard::Quote;
int Slash = sf::Keyboard::Slash;
int BackSlash = sf::Keyboard::BackSlash;
int Tilde = sf::Keyboard::Tilde;
int Equal = sf::Keyboard::Equal;
int Dash = sf::Keyboard::Dash;
int Space = sf::Keyboard::Space;
int Return = sf::Keyboard::Space;
int BackSpace = sf::Keyboard::BackSpace;
int Tab = sf::Keyboard::Tab;
int PageUp = sf::Keyboard::PageUp;
int PageDown = sf::Keyboard::PageDown;
int End = sf::Keyboard::End;
int Home = sf::Keyboard::Home;
int Insert = sf::Keyboard::Insert;
int Delete = sf::Keyboard::Delete;
int Add = sf::Keyboard::Add;
int Subtract = sf::Keyboard::Subtract;
int Multiply = sf::Keyboard::Multiply;
int Divide = sf::Keyboard::Divide;
int Left = sf::Keyboard::Left;
int Right = sf::Keyboard::Right;
int Up = sf::Keyboard::Up;
int Down = sf::Keyboard::Down;
int Numpad0 = sf::Keyboard::Numpad0;
int Numpad1 = sf::Keyboard::Numpad1;
int Numpad2 = sf::Keyboard::Numpad2;
int Numpad3 = sf::Keyboard::Numpad3;
int Numpad4 = sf::Keyboard::Numpad4;
int Numpad5 = sf::Keyboard::Numpad5;
int Numpad6 = sf::Keyboard::Numpad6;
int Numpad7 = sf::Keyboard::Numpad7;
int Numpad8 = sf::Keyboard::Numpad8;
int Numpad9 = sf::Keyboard::Numpad9;
int F1 = sf::Keyboard::F1;
int F2 = sf::Keyboard::F2;
int F3 = sf::Keyboard::F3;
int F4 = sf::Keyboard::F4;
int F5 = sf::Keyboard::F5;
int F6 = sf::Keyboard::F6;
int F7 = sf::Keyboard::F7;
int F8 = sf::Keyboard::F8;
int F9 = sf::Keyboard::F9;
int F10 = sf::Keyboard::F10;
int F11 = sf::Keyboard::F11;
int F12 = sf::Keyboard::F12;
int F13 = sf::Keyboard::F13;
int F14 = sf::Keyboard::F14;
int F15 = sf::Keyboard::F15;
#pragma endregion


void ce::SFMLKeyboard::DoBind(lua_State * Lua)
{

	luabridge::getGlobalNamespace(Lua)
		.beginNamespace("Chef")
			.beginClass<SFMLKeyboard>("Input")
				.addStaticFunction("GetKey", &SFMLKeyboard::GetKey)
				.addStaticFunction("GetKeyDown", &SFMLKeyboard::GetKeyDown)
				.addStaticFunction("GetKeyUp", &SFMLKeyboard::GetKeyUp)
			.endClass()
		
		.endNamespace();
	#pragma region Bind Keys
	luabridge::getGlobalNamespace(Lua)
		.beginNamespace("Chef")
			.addVariable("A", &A)
			.addVariable("B", &B)
			.addVariable("C", &C)
			.addVariable("D", &D)
			.addVariable("E", &E)
			.addVariable("F", &F)
			.addVariable("G", &G)
			.addVariable("H", &H)
			.addVariable("I", &I)
			.addVariable("J", &J)
			.addVariable("K", &K)
			.addVariable("L", &L)
			.addVariable("M", &M)
			.addVariable("N", &N)
			.addVariable("O", &O)
			.addVariable("P", &P)
			.addVariable("Q", &Q)
			.addVariable("R", &R)
			.addVariable("S", &S)
			.addVariable("T", &T)
			.addVariable("U", &U)
			.addVariable("V", &V)
			.addVariable("W", &W)
			.addVariable("X", &X)
			.addVariable("Y", &Y)
			.addVariable("Z", &Z)
			.addVariable("Num0", &Num0)
			.addVariable("Num1", &Num1)
			.addVariable("Num2", &Num2)
			.addVariable("Num3", &Num3)
			.addVariable("Num4", &Num4)
			.addVariable("Num5", &Num5)
			.addVariable("Num6", &Num6)
			.addVariable("Num7", &Num7)
			.addVariable("Num8", &Num8)
			.addVariable("Num9", &Num9)
			//.addVariable("Escape", &Escape)
			.addVariable("LControl", &LControl)
			.addVariable("LShift", &LShift)
			.addVariable("LAlt", &LAlt)
			.addVariable("LSystem", &LSystem)
			.addVariable("RControl", &RControl)
			.addVariable("RShift", &RShift)
			.addVariable("RAlt", &RAlt)
			.addVariable("RSystem", &RSystem)
			.addVariable("RBracket", &RBracket)
			.addVariable("LBracket", &LBracket)
			.addVariable("Menu", &Menu)
			.addVariable("SemiColon", &SemiColon)
			.addVariable("Comma", &Comma)
			.addVariable("Period", &Period)
			.addVariable("Quote", &Quote)
			.addVariable("Slash", &Slash)
			.addVariable("BackSlash", &BackSlash)
			.addVariable("Tilde", &Tilde)
			.addVariable("Equal", &Equal)
			.addVariable("Dash", &Dash)
			.addVariable("Space", &Space)
			.addVariable("Return", &Return)
			.addVariable("BackSpace", &BackSpace)
			.addVariable("Tab", &Tab)
			.addVariable("PageUp", &PageUp)
			.addVariable("PageDown", &PageDown)
			.addVariable("End", &End)
			.addVariable("Home", &Home)
			.addVariable("Insert", &Insert)
			.addVariable("Delete", &Delete)
			.addVariable("Add", &Add)
			.addVariable("Subtract", &Subtract)
			.addVariable("Multiply", &Multiply)
			.addVariable("Divide", &Divide)
			.addVariable("Left", &Left)
			.addVariable("Right", &Right)
			.addVariable("Up", &Up)
			.addVariable("Down", &Down)
			.addVariable("Numpad0", &Numpad0)
			.addVariable("Numpad1", &Numpad1)
			.addVariable("Numpad2", &Numpad2)
			.addVariable("Numpad3", &Numpad3)
			.addVariable("Numpad4", &Numpad4)
			.addVariable("Numpad5", &Numpad5)
			.addVariable("Numpad6", &Numpad6)
			.addVariable("Numpad7", &Numpad7)
			.addVariable("Numpad8", &Numpad8)
			.addVariable("Numpad9", &Numpad9)
			.addVariable("F1", &F1)
			.addVariable("F2", &F2)
			.addVariable("F3", &F3)
			.addVariable("F4", &F4)
			.addVariable("F5", &F5)
			.addVariable("F6", &F6)
			.addVariable("F7", &F7)
			.addVariable("F8", &F8)
			.addVariable("F9", &F9)
			.addVariable("F10", &F10)
			.addVariable("F11", &F11)
			.addVariable("F12", &F12)
			.addVariable("F13", &F13)
			.addVariable("F14", &F14)
			.addVariable("F15", &F15)
				.endNamespace();
#pragma endregion
		
}
