package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;"
require "OtherComponent"
require "CameraFollow"
NewComponent = {ID = -1}

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
	self.speed = 1
end

-- Used for initialization
function NewComponent.Start(self)
	self.collision = self.gameObject:AddCollider()
	self.collision:SetFitSprite(true, true, false)
	
end


--Gets called every frame
function NewComponent.Update(self)
	
	--if(self.other.canMove) then
		if Chef.Input.GetKey(Chef.A) == true then
			self.transform:Move(Chef.Vector2f(-1, 0))
			--self.other.canMove = false
		end
		if Chef.Input.GetKey(Chef.D)== true then
			self.transform:Move(Chef.Vector2f(1, 0))
			--self.other.canMove = false
		end
		if Chef.Input.GetKey(Chef.W)== true then
			self.transform:Move(Chef.Vector2f(0, -1))
			--self.other.canMove = false
		end
		if Chef.Input.GetKey(Chef.S)== true then
			self.transform:Move(Chef.Vector2f(0, 1))
			--self.other.canMove = false
		end
	--end

end

function NewComponent.OnCollisionEnter(self, collider)
	print("Enter Collision")
end
function NewComponent.OnCollisionExit(self, collider)
	print("Quit Colliding")
end

