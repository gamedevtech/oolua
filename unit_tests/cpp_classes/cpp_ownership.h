#ifndef CPP_OWNERSHIP_TEST_H_
#	define CPP_OWNERSHIP_TEST_H_

#include <stdexcept>
#include "gmock/gmock.h"
#include "cpp_stub_classes.h"



class OwnershipParamsAndReturns
{
public:
	virtual ~OwnershipParamsAndReturns(){}
	
	virtual void ptr_param(Stub1* ) = 0;
	virtual void ref_2_ptr(Stub1*& ) = 0;
	
	virtual void const_ptr(Stub1 * const ) = 0;
	virtual void ref_2_const_ptr(Stub1 * const& ) = 0;
	
	virtual void ptr_const(Stub1 const * ) = 0;
	virtual void ref_2_ptr_const(Stub1 const * & ) = 0;

	virtual void const_2_ptr_2_const(Stub1 const* const) = 0;
	virtual void ref_2_const_2_ptr_2_const(Stub1 const* const&) = 0;
	
	
	//virtual void ref_2_type(Stub1& ) = 0;//value of stub can change, no ownership change possible
	//virtual void ref_2_const(Stub1 const & ) = 0;//no change of stub possible
	
	

};


class MockOwnershipParamsAndReturns : public OwnershipParamsAndReturns
{
public:
	virtual ~MockOwnershipParamsAndReturns(){}
	MOCK_METHOD1(ptr_param,					void(Stub1* ));
	MOCK_METHOD1(ref_2_ptr,					void(Stub1*& ));
	
	MOCK_METHOD1(const_ptr,					void(Stub1 * const ));
	MOCK_METHOD1(ref_2_const_ptr,			void(Stub1 * const&));

	MOCK_METHOD1(ptr_const,					void(Stub1 const*));
	MOCK_METHOD1(ref_2_ptr_const,			void(Stub1 const*&));
	
	MOCK_METHOD1(const_2_ptr_2_const,		void(Stub1 const* const));
	MOCK_METHOD1(ref_2_const_2_ptr_2_const,	void(Stub1 const* const&));
	
	//MOCK_METHOD1(ref_2_type,				void(Stub1& ));
	//MOCK_METHOD1(ref_2_const,				void(Stub1 const & ));
};



#endif
