package.path = package.path .. ";Lua Scripts/Components/?.lua;Lua Scripts/?.lua;"
require "OtherComponent"

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
	self.camera = self.gameObject:AddCamera()
	self.camera.size = Chef.Vector2f(64, 36)
	self.camera.follow = true
	
	self.collision = self.gameObject:AddCollider()
	self.collision:SetFitSprite(true, true, false)
	
	self.other = self.gameObject:AddLuaComponent(OtherComponent)
	
	
	self.sfx = Chef.Sound("Sounds\\sound.wav")
end


--Gets called every frame
function NewComponent.Update(self)

	if(self.other.canMove)
	then
		if Chef.Input.GetKey(Chef.A) == true then
			self.transform:Move(Chef.Vector2f(-self.speed, 0))
			self.other.canMove = false
		end
		if Chef.Input.GetKey(Chef.D)== true then
			self.transform:Move(Chef.Vector2f(self.speed, 0))
			self.other.canMove = false
		end
		if Chef.Input.GetKey(Chef.W)== true then
			self.transform:Move(Chef.Vector2f(0, -self.speed))
			self.other.canMove = false
		end
		if Chef.Input.GetKey(Chef.S)== true then
			self.transform:Move(Chef.Vector2f(0, self.speed))
			self.other.canMove = false
		end
	end
	
	if Chef.Input.GetKeyDown(Chef.Space) == true then
		self.sfx:PlaySound()
	end

end

--[[function NewComponent.OnCollisionEnter(self, collider)
	print("Hello there")
end
function NewComponent.OnCollisionExit(self, collider)
	print("Auf Wiedersehen")
end
function NewComponent.OnCollisionStay(self, collider)
	print("Stay")
end]]--

function NewComponent.OnTriggerEnter(self, collider)
	print("Trigger Enter")
end
function NewComponent.OnTriggerExit(self, collider)
	print("Trigger Exit")
end
function NewComponent.OnTriggerStay(self, collider)
	print("Trigger Stay")
end