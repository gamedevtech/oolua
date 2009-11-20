#include "common_generate.h"
#include "lua_function_generate.h"

namespace
{
	char tab[] = "\t";
}
void operator_create(std::ofstream &f,int params)
{
	f<<tab<<"template<typename FUNC";
	for(int i = 1; i<=params;++i)
	{
		f<<",typename P"<<i;
	}
	f<<">\n";

	f<<tab<<"bool operator()(FUNC const&  func_name";
	for(int j = 1;j<=params;++j)
	{
		f<<",P"<<j<<" p"<<j;
	}
	f<<")\n";

	f<<tab<<"{\n" 
	<<tab<<tab<<"set_function(func_name);\n";
	for(int k=1;k<=params;++k)
	{
		if(k==1)f<<tab<<tab;
		f<<"push2lua(m_lua,p"<<k<<"); ";
	}
	f<<"\n"
	<<tab<<tab<<"return call("<<params<<");\n"
	<<tab<<"}\n";
}
void rest_of_struct_body(std::ofstream&f)
{
	f<<tab<<"void bind_script(lua_State* const lua);\n"
	<<"private:\n"
	<<tab<<"bool call(int const& count);\n"
	<<tab<<"void set_function(std::string const& func);\n"
	<<tab<<"void set_function(Lua_func_ref const& func);\n"
	<<tab<<"lua_State* m_lua;\n";
}
void lua_function_header(std::string & save_directory,int maxParams)
{
	std::string fileName("lua_function.h");
	std::string file = save_directory + fileName;
	std::ofstream f( file.c_str() );
	include_guard_top(f,"LUA_FUNCTION_H_");
	add_file_header(f,fileName);


	include_header(f,"lua_includes.h");
	include_header(f,"fwd_push_pull.h");
	include_header(f,"lua_ref.h");
	//include_header(f,"oolua_exception.h");

	f<<"namespace OOLUA\n{\n";	

	f<<
"///////////////////////////////////////////////////////////////////////////////\n\
///  Lua_function\n\
///  Struct which is used to call a lua function.\n\
///  @remarks\n\
///  The Lua function can either be called by name(std::string) or with the\n\
///  use a Lua reference which is stored in a Lua_func.\n\
///////////////////////////////////////////////////////////////////////////////\n";
	f<<"struct Lua_function\n"
	<<"{\n";

	for(int i = 0; i<=maxParams; ++i)
	{
		operator_create(f,i);
	}
	rest_of_struct_body(f);

	f<<"\n};";//end struct
	f<<"\n}\n";//end namespace


	include_guard_bottom(f);
}