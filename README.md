# Chef-Engine
Chef Engine is a game engine made in C++. 


The engine is composition-based using components much like those in Unity Engine.

Rendering to the window and using sprites and such is made by using SFML.www.sfml-dev.org/

The Engine has support for .TMX-files exported from Tile Editor. www.mapeditor.org/
The .TMX-files are loaded using TMX Parser. The fork we're using of TMX Parser: www.github.com/HoggeL/tmxparser

We use LuaBridge to be able to script in Lua. LuaBridge: https://github.com/vinniefalco/LuaBridge
