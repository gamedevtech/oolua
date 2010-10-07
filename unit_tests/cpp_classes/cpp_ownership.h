#ifndef CPP_OWNERSHIP_TEST_H_
#	define CPP_OWNERSHIP_TEST_H_

#include <stdexcept>
#include "cpp_stub_classes.h"


class OwnershipParamsAndReturns
{
public:
	OwnershipParamsAndReturns()
		:m_acquired_ptr(0)
	{}
	~OwnershipParamsAndReturns()
	{
		delete m_acquired_ptr;
	}
	void cpp_acquire_pointer(Stub1* stub)
	{
		m_acquired_ptr = stub;
	}
	void lua_acquire_pointer(Stub1*& stub)
	{
		stub = new Stub1;
	}
	Stub1* returns_new_stub()
	{
		return new Stub1;
	}
	Stub1 returns_stack_stub()
	{
		return Stub1();
	}
	Stub1& return_reference_to_stub()
	{
		return m_stub_member;
	}
	Stub1* returns_cpp_owned_ptr()
	{
		return & m_stub_member;
	}
	Stub1 const* returns_cpp_owned_ptr_to_const()
	{
		return &m_stub_member;
	}

	OwnershipParamsAndReturns(OwnershipParamsAndReturns&);
	OwnershipParamsAndReturns& operator =(OwnershipParamsAndReturns const& );
	Stub1* m_acquired_ptr;
	Stub1 m_stub_member;
};


#endif
