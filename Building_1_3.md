Building OOLua version 1.3


# Introduction #
Most of [Building](Building.md) is relevant for 1.3, the differences are listed below.

# Scripts #
Build and test scripts have been moved to the build\_scripts directory and are required to be run from this directory, not as stated in [Building#Build\_Scripts](Building#Build_Scripts.md) as being run from the root.


# Visual Studio #
Visual Studio 2010 (vs10) is not supported currently by premake, yet if you have vs10 installed and run
```
premake4 vs2010
```
this will generate a vs9 projects then use the update tool to convert to vs10. As vs10 adds files which have not been created directly by premake a specific clean operation has been added to the premake script, this is run via
```
premake4 cleanVS10
```
Scripts to build a local install, build and run unit test etc. have been added for vs10 in the script directory.

# Config #
A configuration header is now included to control what features are present in the library, see [oolua\_config.h](http://code.google.com/p/oolua/source/browse/trunk/include/oolua_config.h) for more information. To turn a feature on, define it to have a default value of 1 in config or predefine it to have this value.

|Macro|Default value|Description|
|:----|:------------|:----------|
|OOLUA\_RUNTIME\_CHECKS\_ENABLED | 1 |Checks that a type being pulled off the stack is of the correct type. If this is a proxy type, it also checks the userdata on the stack was created by OOLua|
|OOLUA\_STD\_STRING\_IS\_INTEGRAL|1 |If 1 Allows std::string to be a parameter or a return type for a function. <br />**NOTE: This is always by value**.|
|OOLUA\_SAFE\_ID\_COMPARE|1 |If 1 then checks id lengths and if the same compares with a memcmp.<br />If 0 compares the address' of the id strings|
|OOLUA\_USE\_EXCEPTIONS|0 |If 1 Throws exceptions from C++ code. This could be the return of a pcall when pulling an incorrect type of the stack if. <br />**See** [Building\_1\_3#Error\_Note](Building_1_3#Error_Note.md)|
|OOLUA\_STORE\_LAST\_ERROR|1 |When an error occurs, the error is stored in the Lua registry and is retrievable via OOLUA::get\_last\_error(lua); <br />**See** [Building\_1\_3#Error\_Note](Building_1_3#Error_Note.md)|
|OOLUA\_DEBUG\_CHECKS|1 |Checks for null pointers adds a stack trace to messages called within pcall. <br />**Note: Default value is when complied as a debug version of the library**.|

## Error Note ##
It is an error to have both OOLUA\_USE\_EXCEPTIONS and OOLUA\_STORE\_LAST\_ERROR set to 1

# File generator #
The library comes with a file generator project which when compiled is a command line executable. This file generates DSL files with limits set via the command line.
|Name|Default value if not defined|Description|
|:---|:---------------------------|:----------|
|--classFunctions|15|Maximum number of member functions a class can register.|
|--cppParams|8 |Maximum parameters an OOLua registered C++ member function can have.|
|--luaParams|10|Maximum parameters an OOLUA::Lua\_function has.|
|--saveDir|`./`|Relative directory to save headers to. Required to be slash postfixed.|
|--constructorParams|5 |Maximum parameters an OOLua registered C++ constructor can have.|
