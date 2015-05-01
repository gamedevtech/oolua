OOLua Binding Framework Cheat Sheet for version 1.4


# Portable #

## lua\_State ##
### OOLUA::Script ###
OOLua is purposely designed not to be dependent on the class OOLUA::Script and therefore passes around it's dependency of a lua\_State. OOLUA::Script is a helper class to easy usage which:
  * Scopes a lua\_State pointer.
  * Provides methods to register types.
  * Binds an instance to call Lua functions.
  * Has member functions for a little state management.
  * Sets up the state to work with OOLua.

### Usage without OOLUA::Script ###
To use the binding without this class and providing your own or 3rd party instance of lua\_State, requires a call to a setup method. This method adds the necessary tables and globals for it to work with the binding.
```
void setup_user_lua_state(lua_State* l);
```


## Pushing values to Lua ##
```
extern lua_State* s;
X value;
OOLUA::push2lua(s,value);
```
Where X is registered class, a registered class with [CheatSheet#Parameter\_type\_traits](CheatSheet#Parameter_type_traits.md) or an integral type. Pushing inserts the input at the top of the stack.


## Pulling values from Lua ##
```
extern lua_State* s;
X value;
OOLUA::pull2cpp(s,value);
```
Where X is registered class, a registered class with [CheatSheet#Parameter\_type\_traits](CheatSheet#Parameter_type_traits.md) or an integral type. Pulls from the top of the stack, see {CheatSheet#Lua\_function\_return\_order].


## Lua references ##
A [Lua\_ref](http://code.google.com/p/oolua/source/browse/trunk/include/lua_ref.h) is a templated class which is a proxy for a value stored in the Lua registry.


## Lua Tables ##
Lua's data structure Table is represented in OOLua using a [OOLUA::Lua\_table\_ref](http://code.google.com/p/oolua/source/browse/trunk/include/lua_ref.h) or [OOLUA::Lua\_table](http://code.google.com/p/oolua/source/browse/trunk/include/lua_table.h).

### Lua\_table ###
A type used to treat the Lua Table reference as a C++ object which has defined operations. <br />
Access and setter methods for error reporting are dependent on [Building#Config](Building#Config.md), except the function safe\_at which always returns a boolean reporting the success or failure of the operation. <br />
Construction of a Lua\_table does not construct a valid registry reference using the default constructor, yet creates an instance that when the member function "valid" is called returns false.<br /> To construct a new table which is represented by a Lua\_table either pure Lua code can be used and passed to the constructor or set via member methoods, alternatively a helper function is present in the library OOLUA::new\_table.
```
OOLUA::Script s;
OOLUA::Lua_table t;//invalid after constructor call
OOLUA::new_table(s,t);//valid after call
```

#### Lua table constructors ####
|Signature|Initialisation|
|:--------|:-------------|
|`Lua_table()`| Default creates an object on which a call to valid returns false|
|`Lua_table(Lua_table_ref const& ref)`|Initialises the reference to be an instance of the same registry reference or an invalid table if ref.valid() == false  |
|`Lua_table(lua_State*  const lua,std::string const& name)`|Sets the lua\_State and calls set\_table|

#### set\_table ####
```
void Lua_table::set_table(std::string const& name);
```
Order of trying to initialise
  * name.empty() == true: Creates am invalid object.
  * name found as a table in Lua global: Swaps the internal Lua\_func\_ref with an instance initialised to an id obtained from the Lua registry.
  * name found as a table in Lua registry: Swaps the internal Lua\_func\_ref with an instance initialised to an id obtained from the Lua registry.
  * else Swaps the internal Lua\_func\_ref with an uninitialised instance.

#### valid ####
```
bool Lua_table::valid()const;
```
Returns a boolean which is the result of checking the state of the internal Lua\_func\_ref.

#### set\_ref ####
```
void Lua_table::set_ref(lua_State* const lua,int const& ref);
```
Initailises the internal Lua\_func\_ref to the id "ref".

#### traverse ####
```
void Lua_table::traverse(Lua_table::traverse_do_function do_);
```
Recursively calls "`do_`" with the next entry on the top of the stack.

#### swap ####
```
void Lua_table::swap(Lua_table & rhs);
```
Swaps the internal Lua\_func\_ref and rhs.m\_table\_ref;

#### safe\_at ####
```
template<typename T,typename T1>bool safe_at(T const& key,T1& value)
```
If the return boolean is true, then "value" contains the result from the table at the index "key".

#### at ####
```
template<typename T,typename T1>T1& at(T const& key,T1& value)
```
The result of calling this function when the table does not contain the key is undefined.

#### set\_value ####
```
void set_value(T const& key,T1 const& value)
```
Inserts the "key" and "value" in the table if key is not present else updates the table's value.

#### remove\_value ####
```
void remove_value(T const& key)
```
Removes the key and also the value from the table.

## Lua function ##
A Lua function can be stored in a Lua\_func\_ref which is a registry copy of the function ( See CheetSheet#Lua\_references] ) or identified as a string.

## Calling a Lua function ##
A Lua function can be called using [Lua\_function](http://code.google.com/p/oolua/source/browse/trunk/include/lua_function.h), of which there is already bound instance available in OOLUA::Script. The Lua\_function class has templated overloaded call operators which take up the amount of parameters defined in [Building#File\_generator](Building#File_generator.md). <br />

### Via name ###
```
func = function() end
```
```
OOLUA::Script s;
s.call("func");
```

### Via reference ###
This example assumes that a function is at the top of the Lua stack.
```
OOLUA::Script s;
OOLUA::Lua_func_ref f;
OOLUA::pull2cpp(s,f);
s.call(f);
```



## Generating a proxy for a class ##

### Typedefs ###
Typedefs allow for more information to be expressed about a class which is having a proxy class created for it, this extra information is placed between the following macros in a comma separated list. For all types which can be inserted into this list see [oolua\_typedefs.h](http://code.google.com/p/oolua/source/browse/trunk/include/oolua_typedefs.h)
  * OOLUA\_TYPEDEFS <br />
  * OOLUA\_TYPEDEFS\_END <br />

For convenience OOLUA\_NO\_TYPEDEFS is available when no further information need be expressed.



### Class constructors ###
1.3 version of the library adds partial support for overloaded constructors, for this the ABI is broken and three new types have been added to oolua\_typedefs.h which can be included inside the OOLUA\_TYPEDEFS macros.
|**Type**|**Meaning**|
|:-------|:----------|
|No\_default\_constructor|There is not a default constructor in the public interface yet there are other constructors.|
|No\_public\_constructors|There are no constructors in the public interface.|
|No\_public\_destructor|There is not a destructor in the public interface and OOLua will not attempt to delete an instance of this type|

If the type No\_public\_constructors is not present in the classes Typedefs then OOLua requires to be told about constructors between the macros :
  * OOLUA\_CONSTRUCTORS\_BEGIN and
  * OOLUA\_CONSTRUCTORS\_END
For convenience instead of using the previous two macros when there are no constructors other than the default, a helper macro is defined OOLUA\_ONLY\_DEFAULT\_CONSTRUCTOR.

When interacting with the Lua stack certain types can not be differentiated between. These include some integral types such as float, int, double etc and types which are of a proxy class type or derived from that type. OOLua implicitly converts between classes in a hierarchy even if a reference is required.<br />
**The constructor which is defined to be used, is the first constructor registered in the class which has the correct amount of parameters and can match the stack entries to the constructors parameter types**

See [expose\_class\_constructors.h](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/bind_classes/expose_class_constructors.h) and [cpp\_constructor\_mock.h](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/cpp_classes/cpp_constructor_mock.h) and [construct.cpp](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/test_classes/construct.cpp)


### No functions of interest for Lua ###
```
struct foo{};

OOLUA_CLASS_NO_BASES(foo)//class has no bases
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END
```

Then in a source file expose the class telling framework that the instance has no functions of interest and providing the name it will be identified by in Lua code(foo).
```
EXPORT_OOLUA_NO_FUNCTIONS(foo)
```

### Has a member function which takes no parameters ###
```
struct foo
{
  int bar();
};

OOLUA_CLASS_NO_BASES(foo)//class has no bases
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
    OOLUA_MEM_FUNC_0(int/*return type*/
                   ,bar/*function name*/)
OOLUA_CLASS_END
```

The line "OOLUA\_MEM\_FUNC\_0(int,bar)" tells the binding that the function takes no parameters, returns an int and the functions name is bar.

Then in a source file expose the class telling the framework that the instance has a function of interest yet no constant member functions, also providing the name it will be identified by in Lua code(foo).
```
EXPORT_OOLUA_FUNCTIONS_1_NON_CONST(foo /*name of class*/
                                  ,bar)/*function being exposed*/
EXPORT_OOLUA_FUNCTIONS_0_CONST(foo)
```

### Has a member function which takes one parameter ###
```
struct foo
{
  int bar(float);
};

OOLUA_CLASS_NO_BASES(foo)
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
    OOLUA_MEM_FUNC_1(int/*return type*/
                   ,bar/*function name*/
                   ,float)/*parameter type*/
OOLUA_CLASS_END
```

```
EXPORT_OOLUA_FUNCTIONS_1_NON_CONST(foo,bar)
EXPORT_OOLUA_FUNCTIONS_0_CONST(foo)
```

### Renaming member functions ###
```
struct RenameFunctions
{
    void func(int);
    int func();
};

OOLUA_CLASS_NO_BASES(RenameFunctions)
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
    OOLUA_MEM_FUNC_1_RENAME(set_func,void,func,int)
    OOLUA_MEM_FUNC_0_RENAME(get_func,int,func)
OOLUA_CLASS_END

EXPORT_OOLUA_FUNCTIONS_2_NON_CONST(RenameFunctions,set_func,get_func)
EXPORT_OOLUA_FUNCTIONS_0_CONST(RenameFunctions)
```

### Abstract class ###
```
struct foo
{
  int bar() = 0;
};

OOLUA_CLASS_NO_BASES(foo)//class has no bases
    OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES/*tell the framework it is abstract*/
    OOLUA_MEM_FUNC_0(int,bar)
OOLUA_CLASS_END
```

```
EXPORT_OOLUA_FUNCTIONS_1_NON_CONST(foo /*name of class*/
                                  ,bar)/*function being exposed*/
EXPORT_OOLUA_FUNCTIONS_0_CONST(foo)
```

### Derived class ###
Expanding on the example in [CheatSheet#Abstract\_class](CheatSheet#Abstract_class.md)
```
struct baz : foo
{
  int bar(){return 1};
};

OOLUA_CLASS(baz) : public Proxy_class<foo>
    OOLUA_BASIC
    OOLUA_NO_TYPEDEFS
    OOLUA_BASES_START foo OOLUA_BASES_END
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END
```
```
EXPORT_OOLUA_NO_FUNCTIONS(baz)
```

OOLUA\_BASIC defines the basic functionality which a proxy class requires, this is automatically added when not using "OOLUA\_CLASS". You can see that the base class functions which have already been exposed do not need to be re-exposed and they will be available for this type.<br />
```
OOLUA_BASES_START foo OOLUA_BASES_END
```
This line tells the binding about the hierarchy again this is automatically added when not using "OOLUA\_CLASS".

### Class operators ###
Class operators are exposed between the OOLUA\_TYPEDEFS\_START and OOLUA\_TYPEDEFS\_END set of macros. The following is a list of the supported operators.
|OOLua type|C++ and Lua operator|
|:---------|:-------------------|
|Less\_op| <|
|Equal\_op|==|
|Not\_equal\_op| !=, not ==|
|Less\_equal\_op|<= Note: Greater than comes for free|
|Div\_op|/ |
|Mul\_op|`*`|
|Sub\_op|- |
|Add\_op|+ |

See [cpp\_class\_ops.h](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/cpp_classes/cpp_class_ops.h), [lua\_class\_ops.h](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/bind_classes/lua_class_ops.h) and [operators.cpp](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/test_classes/operators.cpp)

## Registering a class type with a lua\_State ##
As mentioned [CheatSheet#OOLUA::Script](CheatSheet#OOLUA::Script.md) is only a helper class, so internally it's register function is the same as without.
### With OOLUA::Script ###
```
OOLUA::Script s;
s.register_class<Foo>();
```
or
```
OOLUA::Script s;
Foo* f;
s.register_class(f);
```
### With a lua\_State ###
```
extern lua_State* s;
OOLUA::register_class<Foo>(s);
```
## Registering a class type and all it's bases with a lua\_State ##
```
extern lua_State* s;
OOLUA::register_class_and_bases<Foo>(s);
```
**Note** It is safe to use this function with a type which has no bases.
## Exposing static or C Functions ##
C functions are proxied using a function whose signature matches LuaCFunction
```
int(*)(lua_State*)
```
There is an added requirement that the function parameter of type pointer to lua\_State is named "l" (lower case L)
```
bool someFunc(int, float);

int someFunc(lua_State* l)
{
    OOLUA_C_FUNCTION_2(int,someFunc,int,float)
}
```

```
struct Foo
{
    static void staticMemberFunc();
};

int staticMemberFunc(lua_State* l)
{
    OOLUA_C_FUNCTION_0(void,Foo::staticMemberFunc)
}
```




## Registering static or C Functions in a class ##
Registering a C exposed function "somefunction" as a static function to the type "ClassHasStaticFunction".
```
int somefunction(lua_State* l);
```
```
m_lua->register_class_static<ClassHasStaticFunction>(
                     "static_function"/*name of function*/
                      ,&somefunction);/*function address*/
```
**Note** taking the address of a C function is not required in C++.<br />
This function will then be available when called :
  * As a typed function
```
ClassHasStaticFunction:static_function()
```
  * Called on an instance
```
local obj = ClassHasStaticFunction:new()
obj:static_function()
```
  * Called on an instance which derives from ClassHasStaticFunction
```
local obj = DerivedClassHasStaticFunction:new()
obj:static_function()
```

See [cpp\_static\_and\_c\_functions.h](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/cpp_classes/cpp_static_and_c_functions.h), [expose\_static\_and\_c\_functions.h](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/bind_classes/expose_static_and_c_functions.h), [expose\_static\_and\_c\_functions.cpp](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/bind_classes/expose_static_and_c_functions.cpp) and [static\_function.cpp](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/test_classes/static_function.cpp).



## Parameter type traits ##
Traits can are used on functions parameters:
|Type|Description|
|:---|:----------|
|in\_p|Parameter is only passed to the real member function.|
|out\_p|Parameter or a function return is only passed back to Lua.|
|in\_out\_p|Parameter is passed to function and also back to Lua.|
|cpp\_in\_p|C++ code takes ownership of a pointer.|
|lua\_out\_p|Lua takes ownership of a pointer.|

```
struct foo
{
    foo* create_new_foo();
    void cpp_takes_ownership(foo*);
    int parameter_is_returned(int& i);
};
```

```
OOLUA_CLASS_NO_BASES(foo)
    OOLUA_NO_TYPEDEFS
    OOLUA_MEM_FUNC_0(lua_out_p<foo*>,create_new_foo)
    OOLUA_MEM_FUNC_1(void,cpp_takes_ownership,cpp_in_p<foo*> )
    OOLUA_MEM_FUNC_1(int,parameter_is_returned,in_out_p<int&>)
OOLUA_CLASS_END
```
**Note** for the function "parameter\_is\_returned" the first type will be the return and the second the function parameter.
```
local i=0
return_int, i = obj:parameter_is_returned(i)
```

If parameter traits are not defined then it defaults to OOLUA::in\_p for function parameters and OOLUA::out\_p is used for return values, which is specialised for void types.

Traits can also be use when interacting with the Lua stack by pushing and pulling:
|Type|Description|
|:---|:----------|
|cpp\_acquire\_ptr|C++ code takes ownership of a pointer.|
|lua\_acquire\_ptr|Lua takes ownership of a pointer.|

```
OOLUA::cpp_acquire_ptr<Return_double> ret;
OOLUA::pull2cpp(lua,ret);
delete ret.m_ptr
```

```
OOLUA::lua_acquire_ptr<Foo> input(value);
OOLUA::push2lua(lua,input);
```


See [cpp\_out\_params.h](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/cpp_classes/cpp_out_params.h), [expose\_out\_params.h](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/bind_classes/expose_out_params.h) and [out\_params.cpp](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/test_classes/out_params.cpp)



## Setting and getting global state ##
Anything which can be pushed to Lua using OOLUA::push2lua can also be set as a global in Lua.
```
//setting
int i(0);
extern lua_State* l;
OOLUA::push2lua(l,i);
lua_setglobal(l,"foo");
```
```
//setting to nil
lua_pushnil(l);
lua_setglobal(l,"foo");
```
```
///getting
OOLUA::push2lua(l,i);
lua_get_global(l,"foo");
```
**NOTE** LUA\_GLOBALINDEX is not used here as it is not compatible with Lua 5.2 work releases. <br />

For convenience there are three functions which provide the same functionality as above.
  * `template<typename T>bool OOLUA::set_global(lua_State*,char const*,T& value)`
  * `bool OOLUA::set_global_to_nil(lua_State*,char const*)`
  * `template<typename T>bool OOLUA::get_global(lua_State*,char const*,T& value)`
<br />
See [lua\_globals.cpp](http://code.google.com/p/oolua/source/browse/trunk/unit_tests/test_classes/lua_globals.cpp)
> <br />
# Platform supports variadic macros #
If the platform in use supports variadic macros (more specifically `__VA_ARGS__`) then in most cases a generic macro can be used as follows, unless the portable macro would have contained a 0 (zero).
## Exporting functions ##
```
EXPORT_OOLUA_FUNCTIONS_NON_CONST(foo /*name of class*/
                                  ,bar/*function being exposed*/
                                  ,baz)/*function being exposed*/
EXPORT_OOLUA_FUNCTIONS_0_CONST(foo)//requires 0(zero) in macro
```

## Proxying member functions ##
```
    OOLUA_MEM_FUNC_0(void,foo)//requires 0(zero) in macro
    OOLUA_MEM_FUNC(void,bar,int,SomeClass*)
```

## Proxying C and static functions ##
```
bool someFunc(int, float);

int someFunc(lua_State* l)
{
    OOLUA_C_FUNCTION(int,someFunc,int,float)//When parameter count >=1 no number is required in the macro
}
```

```
struct Foo
{
    static void staticMemberFunc();
};

int staticMemberFunc(lua_State* l)
{
    OOLUA_C_FUNCTION_0(void,Foo::staticMemberFunc)//requires 0(zero) in macro
}
```

## Proxying classes with bases ##
```
struct baz : foo
{
};

OOLUA_PROXY_CLASS(baz,foo)
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END
```
**Note The base macros are not used as seen with [CheatSheet#Derived\_class](CheatSheet#Derived_class.md), this is automatically added with the correct entries**.

## Member functions with and without parameters ##
```
struct foo
{
  int bar();
  void baz(int );
};

OOLUA_PROXY_CLASS(foo)
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
    OOLUA_MEM_FUNC_0(int,bar)//requires 0(zero) in macro
    OOLUA_MEM_FUNC(int,baz,int)//if parameters count >=1 then requires no number in macro
OOLUA_CLASS_END
```
If a function has no parameters then the macro OOLUA\_MEM\_FUNC\_0 or one of its variants is required. On the other hand if it has one or more then the varadic macro OOLUA\_MEM\_FUNC can be used.

## Varadic constructor macro ##
```
struct Foo
{
  Foo();
  Foo(int );
  Foo(int, Bar*);
};
OOLUA_PROXY_CLASS(Foo)
    OOLUA_NO_TYPEDEFS
    OOLUA_CONSTRUCTORS_BEGIN
        /*Foo() is auto generated due to not having No_default_constructor in typedefs*/
        OOLUA_CONSTRUCTOR(int)/*requires no number suffix to macro*/
        OOLUA_CONSTRUCTOR(int,Bar*)/*requires no number suffix to macro*/
    OOLUA_CONSTRUCTORS_END
OOLUA_CLASS_END

```


# Platform is g++ or mscv #
These platforms support the benefits of `__VA_ARGS__` and also support a comma deletion extension which enables suffixes of "0" to be removed from macros.
The platforms also allow registering classes which either do or do not have bases using the same macro OOLUA\_PROXY\_CLASS.

```
struct foo
{
  int bar();
  void baz(int );
};

OOLUA_PROXY_CLASS(foo)//No bases, can use the same macro which register bases
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
    OOLUA_MEM_FUNC(int,bar)//No 0 (zero) required in the macro
    OOLUA_MEM_FUNC(void,baz,int)
OOLUA_CLASS_END
```


```
struct Foo
{
    static void staticMemberFunc();
};

int staticMemberFunc(lua_State* l)
{
    OOLUA_C_FUNCTION(void,Foo::staticMemberFunc)//No 0 (zero) required in the macro
}
```

```
EXPORT_OOLUA_FUNCTIONS_NON_CONST(foo /*name of class*/
                                  ,bar/*function being exposed*/
                                  ,baz)/*function being exposed*/
EXPORT_OOLUA_FUNCTIONS_CONST(foo)//No 0 (zero) required in the macro
```