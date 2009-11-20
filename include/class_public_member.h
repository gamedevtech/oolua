///////////////////////////////////////////////////////////////////////////////
///  @file class_public_member.h
///  Getter and setter functions for the internal classes public member
///  variables.
///  @remarks
///  A getter for a public member(M) of a class(C) creates a function C::get_M 
///  A setter similary creates a function C::set_M similary
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

#ifndef CLASS_PUBLIC_MEMBER_H_
#	define CLASS_PUBLIC_MEMBER_H_

#include "oolua_exception.h"

#define OOLUA_PUBLIC_MEMBER_SET(id)\
int set_##id(lua_State* l)\
{\
	OOLUA_IF_FAIL(!m_this,"m_this is null pointer error in set id")\
 	OOLUA::pull2cpp(l,m_this->id);\
 	return 0;\
}

#define OOLUA_PUBLIC_MEMBER_GET(id)\
int get_##id(lua_State* l)const\
{\
	OOLUA_IF_FAIL(!m_this,"m_this is null pointer error in get id")\
 	OOLUA::push2lua(l,m_this->id);\
 	return 1;\
}

#define OOLUA_PUBLIC_MEMBER_GET_SET(id)\
OOLUA_PUBLIC_MEMBER_GET(id)\
OOLUA_PUBLIC_MEMBER_SET(id)

#endif //CLASS_PUBLIC_MEMBER_H_
