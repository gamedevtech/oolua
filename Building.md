Building OOLua version 1.4 <br />


# Requirements #
## Premake ##
Makefiles, IDE Projects and use of Build Scripts:
> [Premake](http://industriousone.com/premake) - version 4.4
> [Premake quick start](http://industriousone.com/premake-quick-start)

Additionally for Unit Tests or use of Test Unit Scripts:
## Cpp Unit ##
> [CppUnit](http://sourceforge.net/apps/mediawiki/cppunit/) - version 1.12.1
> [Getting to know CppUnit](http://www.ibm.com/developerworks/aix/library/au-ctools2_cppunit/index.html)

## Google Mock ##
> [Google Mock](http://code.google.com/p/googlemock/) - version 1.4 or 1.5
<a href='http://www.youtube.com/watch?feature=player_embedded&v=sYpCyLI47rM' target='_blank'><img src='http://img.youtube.com/vi/sYpCyLI47rM/0.jpg' width='425' height=344 /></a>

# Compile Scripts #
Two type of scripts are present test unit scripts and build scripts.
## Test Scripts ##
Naming is of the format
```
[make or IDE]_tests.[sh or bat]
```
When run from the test\_unit directory these will produce compiler and test unit output saved to disk located in a directory create named "../build\_logs". These scripts clean up any other files produced during there running.

## Build Scripts ##
Naming is of the format
```
[make of IDE]_build.[sh or bat]
```
When run in the test\_unit directory it compiles the library debug and release versions. These static libraries can be found in the "local\_install" directory along with copies of the header files in a directory below this named "oolua". All other files created during the running are deleted.


# Building Makefiles or IDE projects #
OOLua's source and header files can added to your project or be compiled as a static library.
To compile as a static library or to run the UnitTests, Premake version 4 is the recommended method to generate make files/IDE projects. This can either be accomplish using the following details or using the pre-existing bash or bat files( see Compile\_Scripts).

## Premake Format ##
```
premake4 [make or IDE] [target operation system]
```

## Makefile ##
```
premake4 gmake []
```
  * macosx
  * linux

## Xcode ##
```
premake4 xcode3 macosx
```
**macosx is required**

## Visual Studio ##
```
premake4 vs[] windows
```
**windows is required**
  * 2005
  * 2008
  * 2010

## Code::Blocks ##
```
premake4 codeblocks []
```
  * windows
  * linux
  * macosx


# Config #
A configuration header is now included to control what features are present in the library, see [oolua\_config.h](http://code.google.com/p/oolua/source/browse/trunk/include/oolua_config.h) for more information. To turn a feature on, define it to have a default value of 1 in config or predefine it to have this value.

|Macro|Default value|Description|
|:----|:------------|:----------|
|OOLUA\_RUNTIME\_CHECKS\_ENABLED | 1 |Checks that a type being pulled off the stack is of the correct type. If this is a proxy type, it also checks the userdata on the stack was created by OOLua|
|OOLUA\_STD\_STRING\_IS\_INTEGRAL|1 |If 1 Allows std::string to be a parameter or a return type for a function. <br />**NOTE: This is always by value**.|
|OOLUA\_CHECK\_EVERY\_USERDATA\_IS\_CREATED\_BY\_OOLUA|1 |When set to one, everytime a userdata is encountered and it is expected to  have been created by OOLua it is checked and an error occurs if it was not.|
|OOLUA\_USERDATA\_OPTIMISATION|1 |Userdata optimisation which checks for a magic cookie to try and ensure it was created by OOLua, by default this is on when userdata checking is on.  Turning this off by setting it to zero will use a slower yet fully correct method.|
|OOLUA\_USE\_EXCEPTIONS|0 |If 1 Throws exceptions from C++ code. This could be the return of a pcall when pulling an incorrect type of the stack if. <br />**See** [Building#Error\_Note](Building#Error_Note.md)|
|OOLUA\_STORE\_LAST\_ERROR|1 |When an error occurs, the error is stored in the Lua registry and is retrievable via OOLUA::get\_last\_error(lua); <br />**See** [Building#Error\_Note](Building#Error_Note.md)|
|OOLUA\_DEBUG\_CHECKS|1 |Checks for null pointers adds a stack trace to messages called within pcall. <br />**Note: Default value is when complied as a debug version of the library**.|

## Error Note ##
It is an error to have both OOLUA\_USE\_EXCEPTIONS and OOLUA\_STORE\_LAST\_ERROR set to 1

# File generator #
The library comes with a file generator project which when compiled is a command line executable. Running it allows you to easily generate C++ source files with new limits set via the command line.
|Name|Default value if not defined|Description|
|:---|:---------------------------|:----------|
|--classFunctions|15|Maximum number of member functions a class can register.|
|--cppParams|8 |Maximum parameters an OOLua registered C++ member function can have.|
|--luaParams|10|Maximum parameters an OOLUA::Lua\_function has.|
|--saveDir|`./`|Relative directory to save headers to. Required to be slash postfixed.|
|--constructorParams|5 |Maximum parameters an OOLua registered C++ constructor can have.|
