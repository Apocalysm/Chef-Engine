package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;../Chef Engine/Lua Scripts/%Include/?.lua;"
--require "NewComponent"
--require "OtherComponent"
require "include"

mapHandler = Chef.MapHandler()
mapHandler:LoadMap("RefferenceMap.tmx")


object = Chef.GameObject("Green")

comp = object:AddLuaComponent(NewComponent)
object.transform.position = Chef.Vector2f(100, 50)

other = object:AddLuaComponent(OtherComponent)

sprite = object:AddSprite()
sprite:SetSprite("player.png")
sprite.drawOrder = 0
sprite.color = Chef.Color(0, 222, 0, 255)

cameraFollow = object:AddLuaComponent(CameraFollow)