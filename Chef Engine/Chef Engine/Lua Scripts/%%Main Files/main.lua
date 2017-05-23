package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;../Chef Engine/Lua Scripts/%Include/?.lua;"
--require "NewComponent"
--require "OtherComponent"
require "include"

object = Chef.GameObject("Name")

comp = object:AddLuaComponent(NewComponent)
object.transform.position = Chef.Vector2f(150, 150)

sprite = object:AddSprite()
sprite:SetSprite("player.png")
sprite.drawOrder = 10

camera = object:AddCamera()
camera.size = Chef.Vector2f(128, 72)
camera.follow = true

comp.transform.scale = Chef.Vector2f(10, 10)
