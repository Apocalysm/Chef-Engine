/*!

	\section intro_sec Introduction
	This is an introduction for Chef Engine.
	To learn how to use Chef Engine you can look at the example code
	in the 'Examples' menu
*/
--[[
	
	When you want to create a new Component type to add to an object, you
	will use this template where you create your new Component and replace 
	some names in this code.

	For example if you want to create a 'PlayerController' you would replace
	all of the 'ComponentName' in this script. 
    An easy way of doing this is
	marking the phrase you want to replace and pressing Ctrl+H in NotePad++.

	Now you have a functioning component that can easily be added to an object.
	
  ]]

 \code{.unparsed}

-- Here you put all the values you want the component to contain
ComponentName = 
{
	-- ID is a default value that must always be set here and it should be set to -1
	ID = -1
	-- After this you simply add a ',' after ID and then make the next variable/table
	-- you want your component to have
}

-- Gets called the moment you instantiate this component
-- Is called just once in it's lifetime
function ComponentName.Awake(self)
	print("waking up...")
end

-- Used for initialization
function ComponentName.Start(self)	
	print("starting...")
end


--Gets called every frame
function ComponentName.Update(self)
	print("updating")
end

-- This is what you call to create a new instance of the component
function ComponentName.Create(component)		
	-- Copies all the members of this Component to ouput
	output = Chef.LoadComponent(ComponentName)
	
	-- Sets some extra values to make accessibility easier
	output.component = component
	output.gameObject = component.gameObject
	output.transform = component.gameObject.transform

	return output
end

\endcode

*/

