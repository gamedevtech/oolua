#ifndef CPP_CONST_FUNCS_H
#	define CPP_CONST_FUNCS_H_

/*
class C_simple
{
public:
	C_simple():i_(0){}
	C_simple(int i):i_(i){}
	int get_int() const
	{
		return i_;	
	}
	void set_int(int const& i)
	{
		i_ = i;
	}
	void func()
	{
		++i_;
	}
	C_simple const bar()const
	{
		return *this;
	}
	C_simple const* bar1()const
	{
		return this;
	}
private:
	int i_;

};
*/

#include "gmock/gmock.h"

class Constant
{
public:
	Constant():i(0){}
	virtual ~Constant(){}
	virtual int cpp_func_const() const
	{
		return i;
	}
	virtual void cpp_func()
	{
		++i;
	}
private:
	int i;//stop functions being compiled away
};

class ConstantMock : public Constant
{
public:
	MOCK_CONST_METHOD0(cpp_func_const,int ());
	MOCK_METHOD0(cpp_func,void ());
};

#endif
