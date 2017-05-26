package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;../Chef Engine/Lua Scripts/%Include/?.lua;"
--require "NewComponent"
--require "OtherComponent"
require "include"

mapHandler = Chef.MapHandler()
mapHandler:LoadMap("RefferenceMap.tmx")


object = Chef.GameObject("Green")

comp = object:AddLuaComponent(NewComponent)
object.transform.position = Chef.Vector2f(100, 50)

sprite = object:AddSprite()
sprite:SetSprite("player.png")
sprite.drawOrder = 0
sprite.color = Chef.Color(0, 222, 0, 255)

cameraFollow = object:AddLuaComponent(CameraFollow)

object2 = Chef.GameObject("Red")

comp2 = object2:AddLuaComponent(NewComponent)
comp2.speed = 0;
object2.transform.position = Chef.Vector2f(25, 0)

sprite2 = object2:AddSprite()
sprite2:SetSprite("player.png")
sprite2.drawOrder = 0
sprite2.color = Chef.Color(222, 0, 0, 255)