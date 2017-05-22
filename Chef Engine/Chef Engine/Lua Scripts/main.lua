package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;"
require "NewComponent"
require "OtherComponent"


object = Chef.GameObject("Name")

comp = object:AddLuaComponent(NewComponent)
comp.Start(comp)
object.transform.position = Chef.Vector2f(150, 150)

sprite = object:AddSprite()
sprite:SetSprite("player.png")
sprite.drawOrder = 10
object:GetSprite().scale = Chef.Vector2f(10, 10)
