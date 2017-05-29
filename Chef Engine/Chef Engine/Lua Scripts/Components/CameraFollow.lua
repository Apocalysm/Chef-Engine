-- Here you put all the values you want the component to contain
CameraFollow = {ID = -1}

-- This is what you call to create a new instance of the component
function CameraFollow.Create(component)
		
	-- You send the component as a parameter to LoadComponent in C++
	-- This function returns a "new instance" of the sent component
	output = Chef.LoadComponent(CameraFollow)

	output.component = component
	output.gameObject = component.gameObject
	output.transform = component.gameObject.transform
	
	return output
end

-- Gets called the moment you instantiate this component
function CameraFollow.Awake(self)

end

-- Used for initialization
function CameraFollow.Start(self)	
	self.camera = self.gameObject:AddCamera()
	self.camera.size = Chef.Vector2f(64, 36)
	self.camera.follow = true
	self.camera.step = 0.1
end


--Gets called every frame
function CameraFollow.Update(self)
end