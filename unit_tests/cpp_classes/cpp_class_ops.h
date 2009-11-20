///////////////////////////////////////////////////////////////////////////////
///  @file cpp_class_ops.h
///  A simple class to test the class operators which can be made avaible
///  to lua.
///  @remarks
///  This class is to simulate a vector/matrix class.
///  @author Liam Devine @date 19/02/2008
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
#ifndef CPP_CLASS_OPS_TEST_H_
#	define CPP_CLASS_OPS_TEST_H_


class Class_ops
{
public:
	Class_ops(int const & i ):m_i(i){}
	Class_ops():m_i(0){}
	Class_ops( Class_ops const& rhs)
        :m_i(rhs.m_i)
	{}
	int const& geti()const
	{
		return m_i;
	}
	void seti(int const& i)
	{
		m_i = i;
	}
	Class_ops const * pointer_to_const()const
	{
		return this;
	}
	bool operator == (Class_ops const& rhs)const
	{
		return m_i == rhs.m_i;
	}
	bool operator < (Class_ops const& rhs)const
	{
		return m_i < rhs.m_i;
	}
	bool operator <= (Class_ops const& rhs)const
	{
		return m_i <= rhs.m_i;
	}
	Class_ops operator + (Class_ops const& rhs)const
	{
		return Class_ops( m_i + rhs.m_i );
	}
	void operator += (Class_ops const& rhs)
	{
		m_i += rhs.m_i;
	}
	Class_ops operator * (Class_ops const& rhs)const
	{
		return Class_ops(m_i * rhs.m_i);
	}
	void operator *= (Class_ops const& rhs)
	{
		m_i *= rhs.m_i;
	}
	Class_ops operator - (Class_ops const& rhs)const
	{
		return Class_ops(m_i - rhs.m_i);
	}
	Class_ops operator / (Class_ops const& rhs)const
	{
		return Class_ops(m_i / rhs.m_i);
	}
private:
	int m_i;
};

#endif//CPP_CLASS_OPS_TEST_H_
