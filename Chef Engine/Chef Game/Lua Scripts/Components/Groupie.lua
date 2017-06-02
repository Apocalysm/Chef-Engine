Groupie = {ID = -1}

function Groupie.Awake(self)
    print("waking up...")
end


function Groupie.Start(self)
    print("starting...")
end


function Groupie.Update(self)
    self.transform:Move(Chef.Vector2f(-0.2, 0.2))
end


function Groupie.Create(component)
    output = Chef.LoadComponent(Groupie)
    output.component = component
    output.gameObject = component.gameObject
    output.transform = component.gameObject.transform
    return output
end