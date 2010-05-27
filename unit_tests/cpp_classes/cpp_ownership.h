#ifndef CPP_OWNERSHIP_TEST_H_
#	define CPP_OWNERSHIP_TEST_H_

#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////
///  @class A_simple
///  just a simple class
///////////////////////////////////////////////////////////////////////////////
class A_simple
{
public:
	A_simple(){}
	virtual ~A_simple(){}
};

struct A_derived:public A_simple{};

///////////////////////////////////////////////////////////////////////////////
///  @class B_simple
///  another simple class to assign an A_simple ptr to
///////////////////////////////////////////////////////////////////////////////
class B_simple
{
public:
	B_simple():m_a(0){}
	~B_simple(){ delete m_a; }
	void add_A_ptr(A_simple* a)
	{
		if(!a)throw std::runtime_error("pointer passed to B_simple is null");
		delete m_a;
		m_a = a;
	}
	A_simple* create_A()
	{
		return new A_simple;
	}
	B_simple* return_this()
	{
		return this;
	}
	B_simple const* return_this_const()
	{
		return this;
	}
	B_simple(B_simple const&);
	B_simple& operator=(B_simple const&);
protected:
	A_simple* m_a;
};


#endif
