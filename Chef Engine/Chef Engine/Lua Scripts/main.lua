package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;../Chef Engine/Lua Scripts/%Include/?.lua;"
require "NewComponent"
--require "OtherComponent"
require "include"

mapHandler = Chef.MapHandler()
mapHandler:LoadMap("RefferenceMap.tmx")


object = Chef.GameObject("Green")
comp = object:AddLuaComponent(NewComponent)
object.transform.position = Chef.Vector2f(100, 50)
object.transform.scale = Chef.Vector2f(10, 10);

sprite = object:AddSprite()
sprite:SetSprite("player.png")
sprite.drawOrder = 1

textObj = Chef.GameObject("Text")
textObj.transform.scale = Chef.Vector2f(0.1,0.1)
textObj.transform.position = Chef.Vector2f(50, 50)
text = textObj:AddText()
text.font = "fancy font.ttf"
text.string = "This is a text"
text.size = 60
text.drawOrder = 3
text.fillColor = Chef.Color(0, 0, 255, 255)
text.outlineThickness = 5
text.outlineColor = Chef.Color(255, 0, 0, 255)

-- This is the main loop of the engine, it will be called every frame
main = {}
function main.UpdateLoop()

if Chef.Input.GetKeyDown(Chef.Q) == true then
	textObj:Destroy()
	textObj = nil
	end

end