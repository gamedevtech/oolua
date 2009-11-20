#ifndef CPP_CONST_FUNCS_H
#	define CPP_CONST_FUNCS_H_

///\todo add pulling a none constant instance from lua when it is really a constant instance
class C_simple
{
public:
	C_simple():i_(0){}
	C_simple(int i):i_(i){}
	int get_int() const //get method
	{
		return i_;	
	}
	void set_int(int const& i) //set method
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

#endif//CPP_CONST_FUNCS_H_
