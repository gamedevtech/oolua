# News #
This site is no longer in use and development has moved. Please see: http://www.freelists.org/post/oolua/ANN-Google-services-retired
<br />
<br />


# What is OOLua #
OOLua is a C++ binding for [Lua](http://www.lua.org/) which is intended to ease the embedding of Lua in C++ allowing easy access to tables, functions to be called and types to be pushed and pulled from the stack; also C++ in Lua by binding functions, types and class hierarchies. It is compatible with Lua 5.1.`*`, 5.2.`*`, LuaJIT-1.1.8 and LuaJIT2.
<br />
This is not a fully original work, instead it builds on ideas from binding classes using [Luna](http://lua-users.org/wiki/CppBindingWithLunar) and [Lua Technical Note 5](http://www.lua.org/notes/ltn005.html). OOLua uses a [domain specific language](DSL.md) set of macros which internally use templates and generate non intrusive proxies for types.

# Why you should try it #
  * [fast](Speed_comparisons.md)
  * easy to use
  * cross platform
  * free (MIT)
  * no dependencies
  * non intrusive
  * does not use exceptions by default ([can be configured to use exceptions](Building#Config.md))
  * does not use C++ [RTTI](http://en.wikipedia.org/wiki/Run-time_type_information)
  * [test driven](UnitTests.md)

# Dependencies #
The library has no external dependencies yet relies heavily on Loki type lists, which the design and implementation of which is described in [Andrei Alexandrescu’s excellent book](http://erdani.com/index.php/books/modern-c-design/). A rewritten version of the type list templates are included in this library ([Loki is released under MIT](http://loki-lib.sourceforge.net/index.php?n=Main.License) ) which were written as an aid to my learning when I first read the book.

# Usage #
  * Build instructions : [Building](Building.md) <br />
  * Cheat Sheet usage : [CheatSheet](CheatSheet.md)<br />

# Need help #
  * Mailing list : http://groups.google.com/group/oolua-user <br />
  * Twitter account : http://www.twitter.com/OOLua <br />

Have any comments about the library or wish to inform me on which project it is being used, please feel free using the methods listed above.
<br />

&lt;wiki:gadget url="http://www.ohloh.net/p/463031/widgets/project\_users\_logo.xml" height="43" border="0"/&gt;
