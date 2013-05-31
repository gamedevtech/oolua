
--[[
/** [LuaComparisonFile]*/
]]
local clock = os.clock
local N = 10
local times = 1000000

return
{
	vfunc_self = function(object) 
		local ave = 0
		if not object.virtual_func then return -1 end
		for i = 0, N do
			local t0 = clock()
			for i=1,times do
				object:virtual_func()
			end
			local dt = clock()-t0
			if i~=0 then
				ave = ave + dt
			end
		end
		return (ave/N)/times
	end

	,vfunc_cached = function(object) 
		local ave = 0
		if not object.virtual_func then return -1 end
		for i = 0, N do
			local cached_vfunc = object.virtual_func
			local t0 = clock()
			for i=1,times do
				cached_vfunc(object)
			end
			local dt = clock()-t0
			if i~=0 then
			 ave = ave + dt
			end
		end
		return (ave/N)/times
	end

	,mfunc_self = function(object)
		local ave = 0
		for i = 0, N do
			local t0 = clock()
			for i=1,times do
				object:get()
			end
			local dt = clock()-t0
			if i~=0 then
			 ave = ave + dt
			end
		end
		return (ave/N)/times
	end
	--/**[mfuncCachedExample]*/
	,mfunc_cached = function(object)
		local ave = 0
		local func = object.get
		for i = 0, N do
			local t0 = clock()
			for i=1,times do
				func(object)
			end
			local dt = clock()-t0
			if i~=0 then
		 	ave = ave + dt
			end
		end
		return (ave/N)/times
	end
	--/**[mfuncCachedExample]*/
	,memsize = function(creator)
--		local results = {}
		local gc = collectgarbage
--		for i = 1,10 do
			local kb_before, kb_after
			gc('collect')
			kb_before = gc('count')
				local obj = creator()
			gc('collect')	
			kb_after = gc('count')
			
--			results[i] = (kb_after-kb_before)*1024
--			print(results[i],kb_before,kb_after,type(obj))
--		end
--		return results[2]
		return (kb_after-kb_before)*1024
	end
}

--[[
/** [LuaComparisonFile]*/
]]
