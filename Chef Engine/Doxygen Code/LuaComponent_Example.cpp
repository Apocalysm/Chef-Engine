///////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup luaComponent Creating and using your own Component type written in Lua
///  In this group there is instructions for how to create and use your very own Component type made in Lua
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///    \defgroup Creation 1. How to write a new Component Type in Lua
///    \ingroup Creation
///    \ingroup luaComponent
///
///    Here, you're going to find the code needed to create your own Component type in Lua.
///    \n You can just copy the code in the first code-block and replace the all the 'ComponentName'
///    with your own .lua-file's name. Do this simply by marking 'ComponentName' and then press
///    CTRL + H to replace it with whatever their name should be.
///
///    \n But as said earlier, you can either just copy the code-block or read more on this page
///    to know what everything does. The other thing to note is that all the scripts that should be
///    handled as Components, should be placed in the Components-folder that's in the Lua Scripts-folder.
///    In the Components-folder you can then create as many sub-folders as you want.
///    
///    Example for a completed Component that has all the basic functionality of a Component:
///     \code
///
///     ComponentName =
///     {
///         ID = -1
///     }
///
///
///     function ComponentName.Awake(self)
///         print("waking up...")
///     end
///
///
///     function ComponentName.Start(self)
///         print("starting...")
///     end
///
///
///     function ComponentName.Update(self)
///         print("updating")
///     end
///
///
///     function ComponentName.Create(component)
///         output = Chef.LoadComponent(ComponentName)
///
///         output.component = component
///         output.gameObject = component.gameObject
///         output.transform = component.gameObject.transform
///
///         return output
///     end
///
///     \endcode
///
///     We will now go over the code more thoroughly so you will know what it does and how to use it.\n\n
///     
///     This block is where we create the new Lua table that represents our Component.
///     This can be seen as a constructor for a class in C++ or other OOP languages.\n
///
///     One important rule of creating Components is that the .lua-file and the table you create must have the same name
///     For example, the table 'PlayerComponent' must be in a file called 'PlayerComponent.lua'\n
///     
///     You must include the ID variable in all Component-tables and it is best if you declare it at the top of the script and as -1
///     \code
///     PlayerComponent = {ID = -1}
///     \endcode
///
///     \n\n We will now look at the three basic functions 'Awake', 'Start' and 'Update'.
///     These three functions will be called automatically when they're supposed to.
///     None of them have to be included in the Component, but they give important features to your scripts\n\n
///
///     Awake: This is called as soon as you instantiate the Component.
///     It is called once in the Component's lifetime\n
///
///     One thing to note when creating a function in a Lua Component is that you have to send
///     a variable 'self' in the function parameters, this should be a reference to the Component instance you
///     have created in another script. You need a variable like that to know which specific values to use.
///     The Awake function is where you should create different variables that doesn't need references to things such
///     as the GameObject the component belongs to or that GameObject's Transform component.
///     \code
///         function ComponentName.Awake(self)
///             -- Creates a new variable called 100 and sets it to health
///             self.health = 100
///         end
///     \endcode
///
///     \n Start: This function will be called once in the Component's lifetime just before the first time Update
///     is called. Here, just as all functions, you need to send 'self' as a parameter. This is where you want to cre
///     \code
///         function ComponentName.Start(self)
///             -- Moves the GameObject to a new position
///             self.transform.position = Chef.Vector2f(250, 400)
///         end
///     \endcode
///
///     \n Update: This function is called every frame. This is the function where you will probably write most of
///     the gameplay logic. Once again you will need a reference to 'self' so you can access the specific instance's values
///     \code
///         function ComponentName.Update(self)
///             print("updating")
///         end
///     \endcode
///
///     Just to be clear again, you don't need any of these functions but they give very good features to your Components.
/// 
///     \n\n The last part of the default Component is a function you MUST include in a Component you create, otherwise it will not work.
///     This function is called from C++ and basically copies everything in the Component you're currently in to a new instance of the
///     Component. As you can see you can also define more values to the new instance 'output'. The argument 'component' represents the
///     actual LuaComponent in C++ that holds several values as you can see. These values are set for easier accessability.
///     \code
///         function ComponentName.Create(component)
///             output = Chef.LoadComponent(ComponentName)
///             
///             output.component = component
///             output.gameObject = component.gameObject
///             output.transform = component.gameObject.transform
///         
///             return output
///         end
///     
///     \endcode
///
///     \n\n To add a new function to a Component you simply do as you would with any other lua-function.
///     See the 'Usage' chapter to know how to use functions and variables from your components created in Lua.
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///    \defgroup Register 2. How to register a Component created in Lua
///    \ingroup Register
///    \ingroup luaComponent
///    
///     The first thing that have to be done to use your new Component is that you have to
///     register it. You register your component by going to 'include.lua' that's in the %Include
///     folder in the Lua Scripts-folder.
///
///     \n Here you will be met with a lot of code, but you don't have to change more than two parts of the script.
///     
///     First you want to "require" the new Component you created. This is done simply by just writing
///     'require "<ComponentName>" under the bottom most written require-statement.
///     \code
///         require "NewComponent"
///         require "OtherComponent"
///         require "YourComponentName"
///         ...
///     \endcode
///
///     \n After that you have to add your Component's name to the table called 'Components' which is simple 
///     to some degree, where you just add a new entry to the table by writing [number] your Component. The problem
///     is that you have to write this in alphabetical order which can be tricky, but it has to be done!
///     \code
///         Components =
///         {
///             --Here you simply add more components as you go
///             [1] = NewComponent,
///             [2] = OtherComponent,
///             [3] = YourNewComponent,
///             [4] = ...
///         }
///     \endcode
///    
///     After you have done this you can now go to any other .lua-script to use it. At the top of the script
///     you have to add the path to the folder your script is in, if it's not already there.
///     \n You will be met with something similiar to this line that you, yourself will have to add to
///     by simply adding the new folder-path and then put a semicolon(;) at the end.
///     
///     \code
///         package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;"
///     \endcode
///     \n After this you have to do the same thing as in 'include.lua' where you write "require <ComponentName>" to include the file.
///
///     \n Now you're ready to use the Component you just created in many ways which will be explained in "3. How to use a Component created in Lua"
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///    \defgroup Usage 3. How to use a Component created in Lua
///    \ingroup Usage
///    \ingroup luaComponent
///
///    You are now ready to use the new Component you created in Lua.
///    First, you want to create a new GameObject to add your Components to.
///    Creating a new GameObject is simple where you only need to call it's constructor and set a name for it.
///    \code
///         object = Chef.GameObject("Name")
///    \endcode
///    
///    \nAfter that, you can add a Component via the function AddLuaComponent() that's in GameObject.
///    Doing that is also simple where you just write the name of the Component to add.
///    \code
///         comp = object:AddLuaComponent(MyComponentType)
///    \endcode
///    One thing to note is that all function calls in Lua are made by referencing the table the function is in
///    , such as GameObject, and then writing a colon(:).
///
///    \n Now you can reference all of the members in MyComponentType so you can do what you want to do with them.
///     And the different default functions will be called automatically when they're supposed to.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////