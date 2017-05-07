package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;"

require "test"

print(comp.enabled)

comp2 = Chef.Component()
comp2.enabled = false
