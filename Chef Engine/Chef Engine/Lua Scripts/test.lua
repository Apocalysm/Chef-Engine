obj = Chef.Object("none");
comp = obj.AddComponent(Transform())

print(obj.name);

obj.name = "Hej";

print(obj.name);

newComp = 
{
	hash = ComponentRef.GetHash();
}

