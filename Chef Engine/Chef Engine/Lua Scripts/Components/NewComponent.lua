NewComponent = {
ID = -1,
--component,
yesNo = "yes"
}


function NewComponent.Create()
	local output = Chef.LoadComponent(NewComponent)
	
	return output
end


-- Used for initialization
function NewComponent.Start()	
	--print("Starting NewComponent")
	--print(NewComponent.ID)
end


--Gets called every frame
function NewComponent.Update()	
	--print("Updating NewComponent")
	--print(NewComponent.ID)
end

