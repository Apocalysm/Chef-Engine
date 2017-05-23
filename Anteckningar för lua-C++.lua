-- RegisterComponent-method that takes a LuaRef as an argument

-- When you write 
obj = GameObject()

comp = NewComponent.Create(103, "name", false)

obj.AddComponent(comp)
-- We will create a new ce::LuaComponent in C++ that will hold a LuaRef to that instance