local compare = require'compare'

	local _factory =
	{
		OOLua = function() return Set_get:new() end
		,SWIG = function() return swig_profile.Set_get() end
		,LuaBind = function() return Set_get() end
		,SLB3 = function() return  Set_get() end
		,LuaBridge = function() return Set_get() end
	}
local do_mfunc = function(name)
	local factory =
	{
		OOLua = function() return Set_get:new() end
		,SWIG = function() return swig_profile.Set_get() end
		,LuaBind = function() return Set_get() end
		,SLB3 = function() return  Set_get() end
		,LuaBridge = function() return Set_get() end
	}

	local creator = factory[name]
	if not creator then 
		print("| " .. name .. " vfunc | unavailable | unavailable |")
		return {name,'vfunc','unavailable','unavailable'}
	end

	local cached = compare.mfunc_cached( creator() )
	local self = compare.mfunc_self( creator() )
	print("| | | |")
	print("| " .. name .. " mfunc | " .. cached .. " | " .. self.. " |")
	return {name,'mfunc',cached,self}
end


local do_vfunc = function(name)
	local factory =
	{
		OOLua = function() return ProfileMultiBases:new() end
		,SWIG = function() return swig_profile.ProfileMultiBases() end
		,LuaBind = function() return ProfileMultiBases() end
		,SLB3 = function() return  ProfileMultiBases() end
		--[[
		,LuaBridge = function() return ProfileMultiBases() end
		LuaBridge does not support multiple inheritance
		]]
	}

	local creator = factory[name]
	if not creator then 
		print("| " .. name .. " vfunc | unavailable | unavailable |")
		return {name,'vfunc','unavailable','unavailable'}
	end
	local cached = compare.vfunc_cached( creator() )
	local self = compare.vfunc_self( creator() )
	print("| " .. name .. " vfunc | " .. cached .. " | " .. self .. " |")
	return {name,'vfunc',cached,self}
end

vfunc = function(name) 
	do_vfunc(name) 
end

mfunc = function(name) 
	--print(name, 'mfunc_mem_size',compare.memsize(_factory[name]) )
	do_mfunc(name) 
end

test_ud_check = function(name)
	local obj = _factory[name]()
	obj.get(ProfileMultiBases:new())
end
