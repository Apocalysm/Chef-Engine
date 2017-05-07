--package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;"

require "paths"

print(second.comp2.enabled)

comp = Chef.Component()

local publicClass={}

function publicClass.helloWorld()
		print("Hello World")
end

return publicClass
