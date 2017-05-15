package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;"

require "NewComponent"

object = GameObject("LuaObject")

comp = NewComponent.Create(103, "name", false)

object.AddLuaComponent(comp)