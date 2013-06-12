local add_if_best = function(best,test,result_type,result,library_name)
	if --[[type(result) == 'string' and--]] result == 'unavailable' then return end

	if not best[test] then
		best[test] = { [result_type] = {name = library_name, value = tonumber(result)} }
	elseif not best[test][result_type] then
		best[test][result_type] = {name = library_name, value = tonumber(result)}
	elseif tonumber(result) < best[test][result_type].value then
		best[test][result_type].name = library_name
		best[test][result_type].value = tonumber(result)
	end
end

local function write_output(results,section_name, ud_check_type )
	print('\\section ' .. section_name ..' ' .. ud_check_type)
	print([[
| Lua imp || mfunc  |       || vfunc  |       || param  |       |
| :-----: || :----- | :---- || :----- | :---- || :----- | :---- |
|         || cached | self  || cached | self  || cached | self  |]])

	for _,v in ipairs(results[ud_check_type]) do
		--print(v.lua_version,v.doxyref)
		io.write('| \\ref '.. v.doxyref ..' "'.. v.lua_version ..'" ')
		for _,test in ipairs({'mfunc','vfunc','class param'}) do
			local _t = v.bests[test]
			io.write('|| ' .._t.cached.name ..'\\n '.._t.cached.value .. '|' .. _t.self.name .. '\\n ' .. _t.self.value)
		end
		print('|')
	end
end

local function parse_data(data)
	local bests_results =
	{ 
		['Userdata checks']={}
		,['No userdata checks']={}
	}
	local _, chunk_end = 0, 0

	while data:find('\\section',chunk_end+1) do
		local doxyref, lua_version, ud_checks
		_,chunk_end,doxyref,lua_version,ud_checks = string.find(data,'section%s+([%a%d]+)%s([%a%s%d%p]-)%s:%s([%a%s]-)\n',chunk_end)

		local bests = {}
		bests_results[ud_checks][#bests_results[ud_checks] +1 ] 
				= { ['bests']=bests,['doxyref']=doxyref,['lua_version']=lua_version }

		_,chunk_end = data:find('\n.-\n.-\n',chunk_end)--skip 3 new lines are from the end of section
		chunk_end=chunk_end-1 --back up to the new line
		--library tests start with ||||
		while data:find('^\n|%s|%s|%s|\n',chunk_end+1) do
			_,chunk_end = data:find('\n.-\n',chunk_end+1)
			--how many more tests? they each start with |%sname%s
			--so we need to get the first one then check the others against it
			chunk_end=chunk_end-1--back up to the new line and anchor it
			local library = string.match(data,'^\n|%s([%a%d]-)%s',chunk_end+1)
			while string.match(data,'^\n|%s([%a%d]-)%s',chunk_end+1) == library do
				_,chunk_end, library, test, cached, self = data:find('|%s([%a%d]-)%s([%a%s]-)%s|%s(.-)%s|%s(.-)%s|',chunk_end+1)
				add_if_best(bests,test,'cached',cached,library)
				add_if_best(bests,test,'self',self,library)
			end
		end
	end
	return bests_results
end

local f , err = io.open('profile.txt','r')
if err then error(err) end
local data = f:read('*a')
f:close()

local results = parse_data(data)
print('/** \\page LibraryComparisonOverview Comparison overview')
write_output(results,'LuaBestChecks','Userdata checks')
print('<p>')
write_output(results,'LuaBestNoChecks','No userdata checks')
print('*/')

