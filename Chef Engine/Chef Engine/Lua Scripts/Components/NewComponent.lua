local NewComponent = {ID = componentIDCounter++};

-- Used for initalization
NewComponent:Start = function()
	print("Start");
end

-- Gets called every frame
NewComponent:Update = function()
	print("Updating...");
end

NewComponent:SomethingElse()
	print("Something Else");
end

return NewComponent;