-- This is where you put references to all the components you create in Lua

-- You have to include all the paths to all the component script
-- i.e all the scripts in the Components folder and all it's subfolders
package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;"

-- You then have to write require "<filename>" for all the Component scripts
require "NewComponent"
require "OtherComponent"

Components = 
{
	-- Here you simply add more components as you go
	[1] = NewComponent,
	[2] = OtherComponent
	
}

local IDTicker = 0

-- Loops through the table above and gives every component their own ID
for i = 1, #Components do
	Components[i].ID = IDTicker
	IDTicker = IDTicker + 1
end