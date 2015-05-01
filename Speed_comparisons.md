OOLua Binding Framework speed compared to other bindings.


# Introduction #
For these profile tests the following libraries were used:
  * Luabind 0.9.1 **Note**: There is no official version which supports Lua 5.2 so instead the following version was used: [Thomas Nelson's fork](http://github.com/ThomasNelson/luabind/tree/TomN-Lua52%2Bfactories%2Bstl)  <br />Using the defines LUABIND\_NO\_ERROR\_CHECKING and LUABIND\_DONT\_COPY\_STRINGS and Boost 1.4.0
  * OOLua 1.4 Using defines [OOLUA\_RUNTIME\_CHECKS\_ENABLED](Building#Config.md) == 1 [OOLUA\_CHECK\_EVERY\_USERDATA\_IS\_CREATED\_BY\_OOLUA](Building#Config.md) == 1, [OOLUA\_USERDATA\_OPTIMISATION](Building#Config.md) ==1
> > Times also shown when using OOLUA\_RUNTIME\_CHECKS\_ENABLED ==  0
  * Swig 2.0.1

Using a machine with the following CPU
```
Intel(R) Core(TM)2 Duo CPU     P7550  @ 2.26GHz
```

## Setting and getting ##
Getting and setting a member variable via a member function.
C++ code
```
class Set_get
{
public:
	Set_get():_i(0.0){}
	void set(double i)
	{
		_i = i;
	}
	double get()const
	{
		return _i;
	}
private:
	double _i;
};
```

Lua code <br />
Note: this code differs slightly in the construction of class instances for each framework see (library name)_set\_and\_get.lua in the profile directory; yet the construction is not part of the profile test.
```
local N = 10
local ave = 0
local times = 1000000
for i = 0, N do
	local obj = Set_get:new()

	local t0 = os.clock()
	for i=1,times do
		obj:set(i)
		if(obj:get() ~= i)then
			error("failed")
		end
	end
	local dt = os.clock()-t0
	if i~=0 then
	 ave = ave + dt
	end
end

print('OOLua access (average elapsed time):',ave/N)
```
### Access results ###_| **Library** | **Time(sec)**  |
|:------------|:---------------|
|  | Lua 5.1 | Lua 5.2 | LuaJIT2 |
|OOLua|0.3590224|0.3359856|0.2700227|
|Luabind|0.5077312|0.5134535|0.3928163|
|SWIG|0.7512369|0.7709426|0.5926358|
|OOLua no runtime checks|0.3018826|0.3009695|0.2411604|



## Class exchanging ##
The following tests use a class hierarchy as detailed below:
```
class ProfileBase
{
public:
	ProfileBase():_i(0){}
	virtual ~ProfileBase(){}
	void increment_a_base(ProfileBase* base)
	{
		++base->_i;
	}
	virtual void virtual_func()
	{
		++_i;
	}
	virtual void pure_virtual_func() = 0;
private:
	int _i;
};

class ProfileAnotherBase
{
public:
	virtual ~ProfileAnotherBase(){}
};
class ProfileDerived : public ProfileBase
{
public:
	virtual ~ProfileDerived(){}
	virtual void pure_virtual_func()
	{
		++_i;
	}
private:
	int _i;
};

class ProfileMultiBases : public ProfileDerived, public ProfileAnotherBase
{
public:
	void virtual_func()
	{
		++_i;
	}
private:
	int _i;
};
```

### Passing a derived class in Lua to a C++ member class that wants a base ###
Lua code <br />
Note: this code differs slightly in the construction of class instances for each framework see (library name)_derived.lua in the profile directory; yet the construction is not part of the profile test.
```
local N = 10
local ave = 0
local times = 1000000

for i = 0, N do
	local obj = ProfileDerived:new()
	local increment_me = ProfileDerived:new()

	local t0 = os.clock()
	for i=1,times do
		obj:increment_a_base(increment_me)
	end
	local dt = os.clock()-t0
	if i~=0 then
	 ave = ave + dt
	end
end

print('OOLua passing derived to a function that wants a base  (average elapsed time):',ave/N)
```_

#### Wants base results ####
| **Library** | **Time(sec)** | |
|:------------|:--------------|:|
|  | Lua 5.1 | Lua 5.2 | LuaJIT2 |
|OOLua|0.1925849|0.196252|0.1694646|
|Luabind|0.3344658|0.3699374|0.3107969|
|SWIG|0.347758|0.3456323|0.2810876|
|OOLua no runtime checks|0.1772717|0.1947286|0.1425415|

### Passing a derived class which uses multiple inheritance in Lua to a C++ member class that wants a base ###
Lua code <br />
Note: this code differs slightly in the construction of class instances for each framework see (library name)_derived.lua in the profile directory; yet the construction is not part of the profile test.
```
local N = 10
local ave = 0
local times = 1000000
for i = 0, N do
	local obj = ProfileDerived:new()
	local increment_me = ProfileMultiBases:new()

	local t0 = os.clock()
	for i=1,times do
		obj:increment_a_base(increment_me)
	end
	local dt = os.clock()-t0
	if i~=0 then
	 ave = ave + dt
	end
end

print('OOLua passing derived with multiple bases to a function that wants a base  (average elapsed time):',ave/N)
```_

#### Multiple inheritance wants base results ####
| **Library** | **Time(sec)**  | |
|:------------|:---------------|:|
|  | Lua 5.1 | Lua 5.2 | LuaJIT2 |
|OOLua|0.2057114|0.2099513|0.1807507|
|Luabind|0.3404258|0.3745065|0.3139187|
|SWIG|0.3550647|0.3597586|0.3155249|
|OOLua no runtime checks|0.1852408|0.2143713|0.1622692|

The following test should give the same results per library, yet I wanted to check this.
### Calling a virtual function ###
Lua code <br />
Note: this code differs slightly in the construction of class instances for each framework see (library name)_derived.lua in the profile directory; yet the construction is not part of the profile test.
```
local N = 10
local ave = 0
local times = 1000000
for i = 0, N do
	local obj = ProfileMultiBases:new()

	local t0 = os.clock()
	for i=1,times do
		obj:virtual_func()
	end
	local dt = os.clock()-t0
	if i~=0 then
	 ave = ave + dt
	end
end

print('OOLua virtual function  (average elapsed time):',ave/N)
```_


#### Calling a virtual function results ####
| **Library** | **Time(sec)**  | |
|:------------|:---------------|:|
|  | Lua 5.1 | Lua 5.2 | LuaJIT2 |
|OOLua|0.1298764|0.1328911|0.1081259|
|Luabind|0.2508799|0.2763377|0.2238482|
|SWIG|0.3185289|0.3184858|0.2458188|
|OOLua no runtime checks|0.1226391|0.1297259|0.0939919|

### Calling a pure virtual function ###
Lua code <br />
Note: this code differs slightly in the construction of class instances for each framework see (library name)_derived.lua in the profile directory; yet the construction is not part of the profile test.
```
local N = 10
local ave = 0
local times = 1000000
for i = 0, N do
	local obj = ProfileMultiBases:new()

	local t0 = os.clock()
	for i=1,times do
		obj:pure_virtual_func()
	end
	local dt = os.clock()-t0
	if i~=0 then
	 ave = ave + dt
	end
end

print('OOLua pure virtual function  (average elapsed time):',ave/N)
```_

#### Calling a pure virtual function results ####
| **Library** | **Time(sec)**  | |
|:------------|:---------------|:|
|  | Lua 5.1 | Lua 5.2 | LuaJIT2 |
|OOLua|0.1318034|0.1328911|0.1088815|
|Luabind|0.2514496|0.2763377|0.2238482|
|SWIG|0.3195146|0.3221236|0.2461681|
|OOLua no runtime checks|0.1215891|0.1281504|0.0961552|

### Calling a pure virtual function on an instance passed to Lua ###
Lua code <br />
Note: this code differs slightly in the construction of class instances for each framework see (library name)_derived.lua in the profile directory; yet the construction is not part of the profile test.
```
func = function(obj)
local N = 10
local ave = 0
local times = 1000000
	for i = 0, N do
		local t0 = os.clock()
		for i=1,times do
			obj:pure_virtual_func()
		end
		local dt = os.clock()-t0
		if i~=0 then
		 ave = ave + dt
		end
	end
	return ave/N
end
```
#### Calling a virtual function in a function results ####_| **Library** | **Time(sec)** | |
|:------------|:--------------|:|
|  | Lua 5.1 | Lua 5.2 | LuaJIT2 |
|OOLua|0.138073|0.129919|0.107684|
|Luabind|0.214728|0.228361|0.190358|
|SWIG|0.321698|0.319418|0.246192|
|OOLua no runtime checks|0.116942|0.130224|0.09406|



# Comparison Criticism #

The comparison of bindings intend to give you some ball park costs and were orginally based on a Gem [Speed\_comparisons#GPG6](Speed_comparisons#GPG6.md). In the past it was considered difficult to read the number and really understand the differences between libraries; additionly that the cost of the method look up should not be part of the comparison. A Lua self call `self:func()` is functionally the same as `self.func(self)` and it would be normal Lua usage to look up the method once, cache the value and to repeatively use this value in a loop or where frequent look up would otherwise occur.

The following module is used to compare a method call via look up and a call using a cached function.
```
local clock = os.clock
local N = 10
local times = 1000000

return
{
	virtual_self = function(object) 
		local ave = 0
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

	,virtual_cached = function(object) 
		local ave = 0
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
}	

```


Although the comparisons ran the same code when timing, it was not simply a case of a one to one mapping between the different libraries. Most concerning was the fact that LuaBind verified a userdata was created by itself whilst SWIG and originally OOLua did not preform this verification, thus OOLua and SWIG benefited whilst LuaBind was penalised.

Depending on your requirements SWIG, OOLua and LuaBind can all be compiled so that they do not perform these userdata checks, the potential problem this introduces can be shown with the following Lua 5.1 snippets:
```
obj.func( newproxy() )
```
or
```
local cached_func = obj.func
cached_func( newproxy() )
```
or
```
obj:func( newproxy() )
```

When an incorrect userdata is encountered which maybe from an external module or from a Lua script such as in the examples; then best case scenario is the library will detect it and worst case is a segfault.

To compile OOLua and LuaBind to use the same behaviour as SWIG
  * OOLua: define OOLUA\_CHECK\_EVERY\_USERDATA\_IS\_CREATED\_BY\_OOLUA  0
  * LuaBind: define LUABIND\_DISABLE\_UD\_CHECK and add the following macro guard to object\_rep.cpp

```
    LUABIND_API object_rep* get_instance(lua_State* L, int index)
    {
        object_rep* result = static_cast<object_rep*>(lua_touserdata(L, index));

#ifndef LUABIND_DISABLE_UD_CHECK
        if (!result || !lua_getmetatable(L, index))
            return 0;

        lua_rawgeti(L, -1, 1);

        if (lua_tocfunction(L, -1) != &get_instance_value)
            result = 0;

        lua_pop(L, 2);
#endif
        return result;
    }
```


|Assume library created UD |	5.1 		|					| 5.2 			|		        |LuaJIT2		|				|
|:-------------------------|:------|:----|:-------|:---------|:--------|:---|
|							| cached 	 	|	self 			| cached 		| self 		| cached 		| self 	 	|
|OOLua 					|7.32775e-08	|	1.176892e-07	|8.14448e-08	|1.280367e-07 	|5.54798e-08	|9.4672e-08	|
|SWIG						|8.11648e-08	|	3.133149e-07 	|8.43259e-08	|3.329069e-07	|5.34648e-08	|2.503297e-07	|
|LuaBind 					|1.366249e-07	|	2.224448e-07	|1.460183e-07	|2.310521e-07	|1.083106e-07	|1.842683e-07	|




|Check every UD			|	5.1 		|				| 5.2 			|		        |LuaJIT2		|				|
|:----------------|:------|:---|:-------|:---------|:--------|:---|
|							| cached 	 	|	self 		| cached 		| self 		| cached 		| self 	 	|
|OOLua cookie checked		|8.64992e-08	|1.324048e-07	|8.69978e-08	|1.3017e-07	|6.17869e-08	|1.064255e-07	|
|OOLua  metatable checked 	|1.230864e-07 	|1.689803e-07 	|1.386653e-07	|1.855458e-07	|1.035429e-07	|1.485158e-07	|
|LuaBind 					|1.789653e-07 	|2.570887e-07	|1.612678e-07 	|2.592235e-07	|1.374707e-07	|2.243405e-07	|


### GPG6 ###
Celes, W., Figueiredo, L.H. and Ierusalimschy, R., "Binding C/C++ Objects to Lua."  Game Programming Gems 6,  Charles River Media, 2006.