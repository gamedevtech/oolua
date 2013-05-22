#ifndef PROXY_CALLER_H_
#	define PROXY_CALLER_H_

///////////////////////////////////////////////////////////////////////////////
///  @file proxy_caller.h
///  @remarks Warning this file was generated, edits to it will not persist if 
///  the file is regenerated.
///  @author Liam Devine
///  \copyright 
///  See licence.txt for more details. \n 
///////////////////////////////////////////////////////////////////////////////
#	include "member_func_helper.h"
#	include "param_traits.h"
#	include "oolua_converters.h"

/** \cond INTERNAL*/

#define OOLUA_CONVERTER(NUM) OOLUA::INTERNAL::Converter<typename P##NUM::pull_type, typename P##NUM::type> p##NUM##_(p##NUM);
#define OOLUA_CONVERTER0
#define OOLUA_CONVERTER1 OOLUA_CONVERTER(1)
#define OOLUA_CONVERTER2 OOLUA_CONVERTER1 OOLUA_CONVERTER(2)
#define OOLUA_CONVERTER3 OOLUA_CONVERTER2 OOLUA_CONVERTER(3)
#define OOLUA_CONVERTER4 OOLUA_CONVERTER3 OOLUA_CONVERTER(4)
#define OOLUA_CONVERTER5 OOLUA_CONVERTER4 OOLUA_CONVERTER(5)
#define OOLUA_CONVERTER6 OOLUA_CONVERTER5 OOLUA_CONVERTER(6)
#define OOLUA_CONVERTER7 OOLUA_CONVERTER6 OOLUA_CONVERTER(7)
#define OOLUA_CONVERTER8 OOLUA_CONVERTER7 OOLUA_CONVERTER(8)

#define OOLUA_PULL_PP_NUM(NUM) typename P##NUM ::pull_type& p##NUM
#define OOLUA_PULL_PP_0
#define OOLUA_PULL_PP_1 ,OOLUA_PULL_PP_NUM(1)
#define OOLUA_PULL_PP_2 OOLUA_PULL_PP_1 , OOLUA_PULL_PP_NUM(2)
#define OOLUA_PULL_PP_3 OOLUA_PULL_PP_2 , OOLUA_PULL_PP_NUM(3)
#define OOLUA_PULL_PP_4 OOLUA_PULL_PP_3 , OOLUA_PULL_PP_NUM(4)
#define OOLUA_PULL_PP_5 OOLUA_PULL_PP_4 , OOLUA_PULL_PP_NUM(5)
#define OOLUA_PULL_PP_6 OOLUA_PULL_PP_5 , OOLUA_PULL_PP_NUM(6)
#define OOLUA_PULL_PP_7 OOLUA_PULL_PP_6 , OOLUA_PULL_PP_NUM(7)
#define OOLUA_PULL_PP_8 OOLUA_PULL_PP_7 , OOLUA_PULL_PP_NUM(8)

#define OOLUA_PPPPARAMS_0
#define OOLUA_PPPPARAMS_1 p1_
#define OOLUA_PPPPARAMS_2 OOLUA_PPPPARAMS_1 ,p2_
#define OOLUA_PPPPARAMS_3 OOLUA_PPPPARAMS_2 ,p3_
#define OOLUA_PPPPARAMS_4 OOLUA_PPPPARAMS_3 ,p4_
#define OOLUA_PPPPARAMS_5 OOLUA_PPPPARAMS_4 ,p5_
#define OOLUA_PPPPARAMS_6 OOLUA_PPPPARAMS_5 ,p6_
#define OOLUA_PPPPARAMS_7 OOLUA_PPPPARAMS_6 ,p7_
#define OOLUA_PPPPARAMS_8 OOLUA_PPPPARAMS_7 ,p8_

#define OOLUA_TF_PARAMS_0
#define OOLUA_TF_PARAMS_1 typename P1,
#define OOLUA_TF_PARAMS_2 OOLUA_TF_PARAMS_1 typename P2,
#define OOLUA_TF_PARAMS_3 OOLUA_TF_PARAMS_2 typename P3,
#define OOLUA_TF_PARAMS_4 OOLUA_TF_PARAMS_3 typename P4,
#define OOLUA_TF_PARAMS_5 OOLUA_TF_PARAMS_4 typename P5,
#define OOLUA_TF_PARAMS_6 OOLUA_TF_PARAMS_5 typename P6,
#define OOLUA_TF_PARAMS_7 OOLUA_TF_PARAMS_6 typename P7,
#define OOLUA_TF_PARAMS_8 OOLUA_TF_PARAMS_7 typename P8,

namespace OOLUA
{
	namespace INTERNAL
	{
		template <typename Return, typename Class, int ReturnIsVoid>struct Proxy_caller;

#		define oolua_caller_num(NUM) \
		template<OOLUA_TF_PARAMS_##NUM typename FuncType > \
		static void call(lua_State* const l,C* m_this,FuncType ptr2mem OOLUA_PULL_PP_##NUM ) \
		{ \
			OOLUA_CONVERTER##NUM \
			typename R::type r( (m_this->*ptr2mem) (OOLUA_PPPPARAMS_##NUM) ); \
			Member_func_helper<R,R::owner>::push2lua(l,r); \
		}
		
		template <typename R, typename C>
		struct Proxy_caller<R,C, 0 >
		{
			oolua_caller_num(0)
			oolua_caller_num(1)
			oolua_caller_num(2)
			oolua_caller_num(3)
			oolua_caller_num(4)
			oolua_caller_num(5)
			oolua_caller_num(6)
			oolua_caller_num(7)
			oolua_caller_num(8)
		};
#		undef oolua_caller_num
		
#		define oolua_caller_num(NUM) \
		template<OOLUA_TF_PARAMS_##NUM typename FuncType > \
		static void call(lua_State* const /*l*/,C* m_this,FuncType ptr2mem OOLUA_PULL_PP_##NUM ) \
		{ \
			OOLUA_CONVERTER##NUM \
			(m_this->*ptr2mem) (OOLUA_PPPPARAMS_##NUM); \
		}

		template <typename R, typename C>
		struct Proxy_caller<R,C, 1 >
		{
			oolua_caller_num(0)
			oolua_caller_num(1)
			oolua_caller_num(2)
			oolua_caller_num(3)
			oolua_caller_num(4)
			oolua_caller_num(5)
			oolua_caller_num(6)
			oolua_caller_num(7)
			oolua_caller_num(8)	
		};
#		undef oolua_caller_num
		
		template <typename Return, int ReturnIsVoid>struct Proxy_none_member_caller;
		
#		define oolua_caller_num(NUM) \
		template<OOLUA_TF_PARAMS_##NUM typename FuncType > \
		static void call(lua_State* const l,FuncType ptr2func OOLUA_PULL_PP_##NUM ) \
		{ \
			OOLUA_CONVERTER##NUM \
			typename R::type r( (*ptr2func) (OOLUA_PPPPARAMS_##NUM) ); \
			Member_func_helper<R,R::owner>::push2lua(l,r); \
		}
		
		template <typename R> 
		struct Proxy_none_member_caller<R,0 > 
		{
			oolua_caller_num(0)
			oolua_caller_num(1)
			oolua_caller_num(2)
			oolua_caller_num(3)
			oolua_caller_num(4)
			oolua_caller_num(5)
			oolua_caller_num(6)
			oolua_caller_num(7)
			oolua_caller_num(8)
		};
#		undef oolua_caller_num
		
#		define oolua_caller_num(NUM) \
		template<OOLUA_TF_PARAMS_##NUM typename FuncType > \
		static void call(lua_State* const /*l*/,FuncType ptr2func OOLUA_PULL_PP_##NUM ) \
		{ \
			OOLUA_CONVERTER##NUM \
			(*ptr2func) (OOLUA_PPPPARAMS_##NUM); \
		}
		
		template <typename R >
		struct Proxy_none_member_caller<R, 1 >
		{
			oolua_caller_num(0)
			oolua_caller_num(1)
			oolua_caller_num(2)
			oolua_caller_num(3)
			oolua_caller_num(4)
			oolua_caller_num(5)
			oolua_caller_num(6)
			oolua_caller_num(7)
			oolua_caller_num(8)
		};
#		undef oolua_caller_num
		
	}//end INTERNAL namespace
}//end OOLUA namespace


#undef OOLUA_CONVERTER
#undef OOLUA_CONVERTER1
#undef OOLUA_CONVERTER2
#undef OOLUA_CONVERTER3
#undef OOLUA_CONVERTER4
#undef OOLUA_CONVERTER5
#undef OOLUA_CONVERTER6
#undef OOLUA_CONVERTER7
#undef OOLUA_CONVERTER8

#undef OOLUA_PULL_PP_NUM
#undef OOLUA_PULL_PP_0
#undef OOLUA_PULL_PP_1
#undef OOLUA_PULL_PP_2
#undef OOLUA_PULL_PP_3
#undef OOLUA_PULL_PP_4
#undef OOLUA_PULL_PP_5
#undef OOLUA_PULL_PP_6
#undef OOLUA_PULL_PP_7
#undef OOLUA_PULL_PP_8

#undef OOLUA_PPPPARAMS_0
#undef OOLUA_PPPPARAMS_1
#undef OOLUA_PPPPARAMS_2
#undef OOLUA_PPPPARAMS_3
#undef OOLUA_PPPPARAMS_4
#undef OOLUA_PPPPARAMS_5
#undef OOLUA_PPPPARAMS_6
#undef OOLUA_PPPPARAMS_7
#undef OOLUA_PPPPARAMS_8

#undef OOLUA_TF_PARAMS_0
#undef OOLUA_TF_PARAMS_1
#undef OOLUA_TF_PARAMS_2
#undef OOLUA_TF_PARAMS_3
#undef OOLUA_TF_PARAMS_4
#undef OOLUA_TF_PARAMS_5
#undef OOLUA_TF_PARAMS_6
#undef OOLUA_TF_PARAMS_7
#undef OOLUA_TF_PARAMS_8

/**\endcond*/
#endif 
