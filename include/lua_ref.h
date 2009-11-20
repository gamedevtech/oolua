///////////////////////////////////////////////////////////////////////////////
///  @file lua_ref.h
///  A wrapper for a lua registry reference in a struct 
///  so that the type is different to an int. Typedefs two types Lua_table_ref & \n
///  Lua_func_ref.
///  @author Liam Devine
///  @email
///  See http://www.liamdevine.co.uk for contact details.
///  @licence
///  This work is licenced under a Creative Commons Licence. \n
///  see: \n
///  http://creativecommons.org/licenses/by-nc-sa/3.0/ \n
///  and: \n
///  http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode \n
///  For more details.
///////////////////////////////////////////////////////////////////////////////
#ifndef LUA_REF_H_
#	define LUA_REF_H_

#include "lua_includes.h"

namespace OOLUA
{

	///////////////////////////////////////////////////////////////////////////////
	///  @class Lua_func_ref
	///  A wrapper for a lua registry reference in a struct 
	///  so that the type is different to an int.
	///
	///  @remarks 
	///  An object wrapper for a value in LUA_REGISTRYINDEX
	///  @author Liam Devine and David O'Reilly @date 01/03/2007
	///////////////////////////////////////////////////////////////////////////////
	template<int ID>
	struct Lua_ref
	{
		Lua_ref(lua_State* const lua,int const& ref);
		explicit Lua_ref(lua_State* const lua);
		Lua_ref();
		Lua_ref& operator =(Lua_ref const& /*rhs*/);//unimplemented
		Lua_ref(Lua_ref const& /*rhs*/);//unimplemented
		~Lua_ref();
		bool valid()const;
		int const& ref()const;
		void set_ref(lua_State* const lua,int const& ref);
		void swap(Lua_ref & rhs);
	private:
		void release();
		lua_State* m_lua;
		int m_ref;
	};
	

	template<int ID>
	Lua_ref<ID>::Lua_ref(lua_State* const lua,int const& ref)
		:m_lua(lua),m_ref(ref)
	{}
	template<int ID>
	Lua_ref<ID>::Lua_ref(lua_State* const lua)
		:m_lua(lua),m_ref(LUA_NOREF)
	{}
	template<int ID>
	Lua_ref<ID>::Lua_ref()
		:m_lua(0),m_ref(LUA_NOREF)
	{}
	template<int ID>
	Lua_ref<ID>::~Lua_ref()
	{
		release();
	}
	template<int ID>
	bool Lua_ref<ID>::valid()const
	{
		return m_lua && m_ref != LUA_REFNIL && m_ref != LUA_NOREF;
	}
	template<int ID>
	int const& Lua_ref<ID>::ref()const
	{
		return m_ref;
	}
	template<int ID>
	void Lua_ref<ID>::set_ref(lua_State* const lua,int const& ref)
	{
		release();
		m_ref = ref;
		m_lua = lua;
	}
	template<int ID>
	void Lua_ref<ID>::release()
	{
		if(m_lua )
		{
			luaL_unref(m_lua,LUA_REGISTRYINDEX,m_ref);
		}
		m_ref = LUA_NOREF;
	}
	template<int ID>
	void Lua_ref<ID>::swap(Lua_ref & rhs)
	{
		lua_State* tl (rhs.m_lua);
		int tr (rhs.m_ref);
		rhs.m_lua = m_lua;
		rhs.m_ref = m_ref;
		m_lua = tl;
		m_ref = tr;
	}



	///\typedef Lua_table_ref
	///Wrapper for a lua table
	typedef Lua_ref<0> Lua_table_ref;
	///\typedef Lua_func_ref 
	///Wrapper for a lua function
	typedef Lua_ref<1> Lua_func_ref;


}
#endif //LUA_REF_H_
