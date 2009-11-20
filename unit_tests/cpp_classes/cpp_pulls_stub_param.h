#ifndef CPP_PULLS_STUB_PARAM_H_
#	define CPP_PULLS_STUB_PARAM_H_

#include "gmock/gmock.h"

struct Stub{};

class Pulls_stub
{
public:
	virtual ~Pulls_stub(){}
	virtual void ref(Stub& )=0;
	virtual void ref_const(Stub const &)=0;
	virtual void ptr(Stub* )=0;
	virtual void ptr_const(Stub const * )=0;
	virtual void const_ptr_const(Stub  const* const )=0;
	virtual void ref_ptr_const(Stub const *& )=0;
	virtual void ref_const_ptr_const(Stub const* const & )=0;
};

class Mock_pulls_stub : public Pulls_stub
{
public:
	MOCK_METHOD1(ref,void (Stub&));
	MOCK_METHOD1(ref_const,void (Stub const &));
	MOCK_METHOD1(ptr,void (Stub*));
	MOCK_METHOD1(ptr_const,void (Stub const * ));
	MOCK_METHOD1(const_ptr_const,void (Stub  const* const ));
	MOCK_METHOD1(ref_ptr_const,void (Stub const *&  ));
	MOCK_METHOD1(ref_const_ptr_const,void (Stub const* const & ));
};

#endif