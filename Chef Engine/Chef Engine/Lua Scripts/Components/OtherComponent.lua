OtherComponent = {
ID = -1,
component
}

function OtherComponent.Create()
	local output = {}
	
	setmetatable(output, OtherComponent)
	
	return output
end

-- Used for initialization
function OtherComponent.Start()
	--print("Starting OtherComponent")
	--print(OtherComponent.ID)
end

--Gets called every frame
OtherComponent.Update = function()
	--print("Updating OtherComponent")
	--print(OtherComponent.ID)
end