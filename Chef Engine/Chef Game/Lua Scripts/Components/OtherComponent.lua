-- Here you put all the values you want the component to contain
OtherComponent = {ID = -1}
	
-- This is what you call to create a new instance of the component
function OtherComponent.Create(component)
		
	-- You send the component as a parameter to LoadComponent in C++
	-- This function returns a "new instance" of the sent component
	output = Chef.LoadComponent(OtherComponent)

	output.component = component
	output.gameObject = component.gameObject
	output.transform = component.gameObject.transform
	
	return output
end

-- Gets called the moment you instantiate this component
function OtherComponent.Awake(self)
	self.timer = 60
	self.countdown = 0
	self.timedecrementer = 20
	self.canMove = true
end

-- Used for initialization
function OtherComponent.Start(self)	

end


--Gets called every frame
function OtherComponent.Update(self)	

	if self.canMove == false then
		if self.countdown <= 0 then 	
			self.countdown = self.timer
			self.canMove = true
		else 
			self.countdown = self.countdown - self.timedecrementer
		end
	end
end