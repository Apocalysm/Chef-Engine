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
sprite.color = Chef.Color(0, 222, 0, 255)

camera = object:AddCamera()
camera.size = Chef.Vector2f(256, 148)
camera.follow = true

object2 = Chef.GameObject("Name")

comp3 = object2:AddLuaComponent(NewComponent)
object2.transform.position = Chef.Vector2f(200, 150)

sprite3 = object2:AddSprite()
sprite3:SetSprite("player.png")
sprite3.drawOrder = 10
sprite3.color = Chef.Color(222, 0, 0, 255)
comp3.speed = 0;

