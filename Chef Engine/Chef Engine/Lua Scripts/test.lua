package.path = package.path .. ";../Chef Engine/Lua Scripts/Components/?.lua;../Chef Engine/Lua Scripts/?.lua;"

require "NewComponent"
--[[
Account = {};

Account.__index = Account;

function Account:Create(balance)
	local acnt = {};
	setmetatable(acnt, Account);
	acnt.balance = balance;
	return acnt;
end

function Account:Withdraw(amount)
	self.balance = self.balance - amount;
end


-- Component.lua
Component = {}

function Component:__call()
	return self:subclass(
end

function Component:subclass(name)
	local output = {}
	setmetatable(output, Component);
	output.name = name;
	return output;
end


-- NewComponent.lua
local Component = require("Component")
local NewComponent = Component:subclass("NewComponent")

...

return NewComponent]]