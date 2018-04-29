split = function(str, delim)
	local t = {}

	if (delim == nil) then
		delim = "%s" -- whitespace
	end

	i = 1
	for s in string.gmatch(str, "([^" .. delim .. "]+)") do
		t[i] = s
		i = i + 1
	end

	return t
end

-- Do NOT use this to load plugins!
-- Only for functions/variables in the plugin's table
include = function(plugin, filename)
	dofile("plugins/" .. plugin.name .. "/" .. filename)
end

LoadPlugin = function(plugin, filename)
	Server.LoadPlugin("plugins/" .. plugin.name .. "/" .. filename)
end

GetTableLength = function(t)
	local length = 0
	for _ in pairs(t) do
		length = length + 1
	end

	return length
end
