package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;"
require "NewComponent"
require "OtherComponent"


object = Chef.GameObject("Name")

comp = NewComponent.Create()
comp.yesNo = "no"
print(comp)
print(comp.ID)
print(comp.yesNo)
newComp = NewComponent.Create()

print(NewComponent.yesNo)
object:AddLuaComponent(comp)

--comp2 = OtherComponent.Create()

--object:AddLuaComponent(comp2)