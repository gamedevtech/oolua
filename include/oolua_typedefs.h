///////////////////////////////////////////////////////////////////////////////
///  @file oolua_typedefs.h
///  Possible members for a Proxy_class typedefs
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
#ifndef OOLUA_TYPEDEFS_H_
# define OOLUA_TYPEDEFS_H_

///  \addtogroup oolua_typedefs
///  @{

///  @struct OOLUA::Abstract
///  The class being mirrored is an abstract class.

///  @struct OOLUA::Less_op
///  Less than operator is defined for the type.

///  @struct OOLUA::Equal_op
///  Equal operator is defined for the type.

///  @struct OOLUA::Not_equal_op
///  Not equal operator is defined for the type.

///  @struct OOLUA::Less_equal_op
///  Less than or equal operator is defined for the type.

///  @struct OOLUA::Div_op
///  Division operator is defined for the type.

///  @struct OOLUA::Mul_op
///  Multiplication operator is defined for the type.

///  @struct OOLUA::Sub_op
///  Subtraction operator is defined for the type.

///  @struct OOLUA::Add_op
///  Addition operator is defined for the type.

namespace OOLUA
{

	struct Abstract{};
	struct Less_op{};
	struct Equal_op{};
	struct Not_equal_op{};
	struct Less_equal_op{};
	struct Div_op{};
	struct Mul_op{};
	struct Sub_op{};
	struct Add_op{};

}
	///  @}
#endif//OOLUA_TYPEDEFS_H_
