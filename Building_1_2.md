Building Makefiles or IDE projects OOLua version 1.2.2
For Version 1.3 differences please see [Building\_1\_3](Building_1_3.md)


# Requirements #
## Premake ##
Makefiles, IDE Projects and use of Build Scripts:
> [Premake](http://industriousone.com/premake) - version 4.2
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
Test Unit Scripts:
Naming is of the format
```
[make or IDE]_tests.[sh or bat]
```
when run in the root directory these will produce compiler and test unit result output saved to disk located in a directory create named "build\_logs". These scripts clean up any other files produced during there running.

# Build Scripts #
Naming is of the format
```
[make of IDE]_build.[sh or bat]
```
when run in the root directory it compiles the library debug and release versions. These static libraries can be found in the "local\_install" directory along with copies of the header files in a directory below this named "oolua". All other files created during the running are deleted.


# Building Makefiles or IDE projects #
OOLUA's source and header files can added to your project or be compiled as a static library.
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

## Code::Blocks ##
```
premake4 codeblocks []
```
  * windows
  * linux
  * macosx

# Further Premake Details #
See [Premake](http://industriousone.com/premake) for options or type
```
premake4 --help
```