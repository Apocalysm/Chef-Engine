-- Here you put all the values you want the component to contain
NewComponent = 
{
	ID = -1
}

-- This is what you call to create a new instance of the component
function NewComponent.Create(component)
		
	-- You send the component as a parameter to LoadComponent in C++
	-- This function returns a "new instance" of the sent component
	output = Chef.LoadComponent(NewComponent)
	
	output.component = component
	output.gameObject = component.gameObject
	output.transform = component.gameObject.transform

	return output
end

-- Gets called the moment you instantiate this component
function NewComponent.Awake(self)
	print("waking up, new...")
	--print(self.ID)
end

-- Used for initialization
function NewComponent.Start(self)	
	print("starting...")
end


--Gets called every frame
function NewComponent.Update(self)
	self.transform:Move(Chef.Vector2f(0.5, 0.1))
end

