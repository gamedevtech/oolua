#ifndef OOLUA_VA_ARGS_H_
#	define OOLUA_VA_ARGS_H_


//TODO check which is the minimum gcc version supporting this
#ifdef __GNUC__
//	SShhhhhhhhh stops gcc generating warnings about the variadic macros
#	pragma GCC system_header
#endif

//TODO vs8 (2005) supports this

//TODO Intel version ??


//The only difference between the code at the following URL and used below, is
//that macro names got an OOLUA prefix as per all macros in the library
//http://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5

#define OOLUA_NARG(...) \
	OOLUA_NARG_DO(__VA_ARGS__,OOLUA_RSEQ_N())

#define OOLUA_NARG_DO(...) \
	OOLUA_ARG_N(__VA_ARGS__)

#define OOLUA_ARG_N( \
	_1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
	_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
	_21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
	_31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
	_41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
	_51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
	_61,_62,_63,N,...) N

#define OOLUA_RSEQ_N() \
	63,62,61,60,                   \
	59,58,57,56,55,54,53,52,51,50, \
	49,48,47,46,45,44,43,42,41,40, \
	39,38,37,36,35,34,33,32,31,30, \
	29,28,27,26,25,24,23,22,21,20, \
	19,18,17,16,15,14,13,12,11,10, \
	9,8,7,6,5,4,3,2,1,0

#define DO_TEST_CONCAT(A,B)\
	A##B

#define TEST_CONCAT(A,B)\
	DO_TEST_CONCAT(A,B)


//NOTE if this file's contents is to be kept, it would be much better if it was generated
//with the other headers in the file_generator executable


#define TEST_OOLUA_MEM_FUNC(return_type,func_name,...)\
	TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__))(return_type,func_name,__VA_ARGS__)

#define TEST_OOLUA_MEM_FUNC_CONST(return_value,func,...)\
	TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__)),_CONST)(return_type,func_name,__VA_ARGS__)

#define TEST_OOLUA_MEM_FUNC_RENAME(new_name,return_value,func_name,...)\
	TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__)),_RENAME)(new_name,return_type,func_name,__VA_ARGS__)

#define TEST_OOLUA_MEM_FUNC_CONST_RENAME(new_name,return_value,...)\
	TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__)),_CONST_RENAME)(new_name,return_type,func_name,__VA_ARGS__)


#define TEST_EXPORT_OOLUA_FUNCTIONS_NON_CONST(ClassType,...)\
	TEST_CONCAT(TEST_CONCAT(EXPORT_OOLUA_FUNCTIONS_,OOLUA_NARG(__VA_ARGS__)),_NON_CONST)(ClassType,__VA_ARGS__)

#define TEST_EXPORT_OOLUA_FUNCTIONS_CONST(ClassType,...)\
	TEST_CONCAT(TEST_CONCAT(EXPORT_OOLUA_FUNCTIONS_,OOLUA_NARG(__VA_ARGS__)),_CONST)(ClassType,__VA_ARGS__)


#define TEST_OOLUA_PUBLIC_INHERIT_1(ClassType) \
		public Proxy_class<ClassType> 

#define TEST_OOLUA_PUBLIC_INHERIT_2(ClassType1,ClassType2) \
	TEST_OOLUA_PUBLIC_INHERIT_1(ClassType1)\
	,TEST_OOLUA_PUBLIC_INHERIT_1(ClassType2)

#define TEST_OOLUA_PUBLIC_INHERIT_3(ClassType1,ClassType2,ClassType3) \
	TEST_OOLUA_PUBLIC_INHERIT_2(ClassType1,ClassType2)\
	,TEST_OOLUA_PUBLIC_INHERIT_1(ClassType3)\


#define TEST_OOLUA_PUBLIC_INHERIT_4(ClassType1,ClassType2,ClassType3,ClassType4) \
	TEST_OOLUA_PUBLIC_INHERIT_3(ClassType1,ClassType2,ClassType3)\
	,TEST_OOLUA_PUBLIC_INHERIT_1(ClassType4)\

#define TEST_OOLUA_PUBLIC_INHERIT(...) \
	TEST_CONCAT(TEST_OOLUA_PUBLIC_INHERIT_,OOLUA_NARG(__VA_ARGS__))(__VA_ARGS__)

#define TEST_OOLUA_CLASS_WITH_BASES(ClassType,...) \
	OOLUA_CLASS(ClassType) : TEST_OOLUA_PUBLIC_INHERIT(__VA_ARGS__) \
	OOLUA_BASIC\
	OOLUA_BASES_START __VA_ARGS__ OOLUA_BASES_END


#endif
