-- Here you put all the values you want the component to contain
OtherComponent = 
{
	ID = -1
}

-- This is what you call to create a new instance of the component
function OtherComponent.Create(component)
		
	-- You send the component as a parameter to LoadComponent in C++
	-- This function returns a "new instance" of the sent component
	output = Chef.LoadComponent(OtherComponent)
	
	output.component = component
	output.gameObject = component.gameObject

	return output
end

-- Gets called the moment you instantiate this component
function OtherComponent.Awake(self)
	print("waking up, other...")
	--print(self.ID)
end

-- Used for initialization
function OtherComponent.Start(self)	
	print("starting...")
end


--Gets called every frame
function OtherComponent.Update(self)	
	--print("update")
end