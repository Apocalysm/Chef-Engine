NewComponent = {
health = 100,
tag = "default",
isDead = false
}

function NewComponent.Create(hp, tag, isDead)
	local output = {}
	setmetatable(output, NewComponent)
	
	output.health = hp
	output.tag = tag
	output.isDead = isDead
	
	print(output.isDead)
	print(output.tag)
	print(output.health)
	
	-- Saves a LuaRef of output in C++ that calls Start/Update
	Chef.RegisterComponent(output);
	
	return output
end

-- Used for initialization
NewComponent.Start = function(NewComponent.Create())
	print("Start")
end

--Gets called every frame
NewComponent.Update = function()
	print("Updating")
	print(NewComponent.tag)
end