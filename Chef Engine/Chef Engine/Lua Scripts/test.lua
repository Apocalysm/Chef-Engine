comp = Chef.Component()

print(comp.enabled)
comp.enabled = false
print(comp.enabled)


local publicClass={}

function publicClass.helloWorld()
		print("Hello World")
end

return publicClass