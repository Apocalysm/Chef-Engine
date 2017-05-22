///////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup luaComponent Writing a new component type in Lua
///  In this group there is instructions for how to create and use your very own Component type made in Lua
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
///    \defgroup Creation
///    \ingroup Creation
///    \ingroup luaComponent
///    \brief How to set up a new Component in Lua
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
///     You must include the ID variable in all Components, you also have to set it but it doesn't matter to what.
///     After that you can simply add a comma(',') to add a new variable or function as we have done in the example below
///     \code
///
///     PlayerComponent =
///     {
///         ID = -1,
///         health = 100,
///         dead = false,
///         ...
///     }
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
///     \code
///         function ComponentName.Awake(self)
///             print("waking up...")
///         end
///     \endcode
///
///     \n Start: This function will be called once in the Component's lifetime just before the first time Update
///     is called. Here, just as all functions, you need to send 'self' as a parameter.
///     \code
///         function ComponentName.Start(self)
///             -- Sets the gameObject's health to 100 and moves it to a new position
///             health = 100
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
/////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
///    \defgroup Usage
///    \ingroup Usage
///    \ingroup luaComponent
///    \brief How to use a Component created in Lua
///    
///
/////////////////////////////////////////////////////////////////////////////////////////////

