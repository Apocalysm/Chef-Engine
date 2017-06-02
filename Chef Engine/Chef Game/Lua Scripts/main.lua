package.path = package.path .. ";Lua Scripts/Components/?.lua;Lua Scripts/?.lua;Lua Scripts/%Include/?.lua;"
require "NewComponent"
--require "OtherComponent"
require "include"

Chef.Window.SetSize(Chef.Vector2u(1280, 720))
Chef.Window.SetFrameRateLimit(60)

mapHandler = Chef.MapHandler()
mapHandler:LoadMap("Maps\\RefferenceMap.tmx")
-- Chef.Music.PlayMusic("Sounds\\music.wav", true)



vec2 = Chef.Vector2f(7,5)

-- This is the main loop of the engine, it will be called every frame
main = {}
function main.UpdateLoop()

end