#ifndef OOLUA_CONVERTERS_H_
#	define OOLUA_CONVERTERS_H_

/** \cond INTERNAL*/

namespace LVD
{
	template<typename T>struct by_reference;
}

namespace OOLUA
{
	namespace INTERNAL 
	{
	template<typename Pull_type,typename Real_type>struct Converter;
	
	template<typename T>
	struct Converter<T*,T&>
	{
		Converter(T*& t):m_t(t){}
		operator T& () const
		{
			return *m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	
	
	template<typename T>
	struct Converter<T*,T>
	{
		Converter(T* t):m_t(t){}
		operator T& () const
		{
			return *m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};

	template<typename T>
	struct Converter<T const*, T>
	{
		typedef char T_has_to_be_by_value[ LVD::by_reference<T>::value ? -1 : 1];
		Converter(T const* t):m_t((T*)t){}
		operator T& () const
		{
			return *m_t;
		}
		Converter& operator = (Converter const&);
		Converter(Converter const&);
		T* m_t;
	};

	template<typename T>
	struct Converter<T,T*>
	{
		Converter(T& t):m_t(t){}
		operator T* () const
		{
			return &m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T& m_t;
	};
	
		
	template<typename T>
	struct Converter<T*,T*&>
	{
		Converter(T*& t):m_t(t){}//added reference
		operator T*& () //const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T*& m_t;//added reference
	};
	
		
	template<typename T>
	struct Converter<T*,T const&>
	{
		Converter(T* t):m_t(t){}
		operator T const&() const
		{
			return *m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	
	template<typename T>
	struct Converter<T*,T const*&>
	{
		Converter(T* t):m_t(t){}
		operator T const*&()
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T const* m_t;
	};
	
	template<typename T>
	struct Converter<T*,T const*>
	{
		Converter(T* t):m_t(t){}
		operator T const*() const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	
	template<typename T>
	struct Converter<T,T*const&>
	{
		Converter(T & t):m_t(t){}
		operator T* /*const*/  () const
		{
			return &m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T & m_t;
	};
	
	template<typename T>
	struct Converter<T,T const*&>
	{
		Converter(T & t):m_t(&t){}
		operator T const*&()
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T const* m_t;
	};
	template<typename T>
	struct Converter<T,T const *const &>
	{
		Converter(T& t):m_t(&t){}
		operator T*const &() const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	template<typename T>
	struct Converter<T*,T *const&>
	{
		Converter(T* t):m_t(t){}
		operator T *const&() const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	template<typename T>
	struct Converter<T*,T const*const&>
	{
		Converter(T* t):m_t(t){}
        operator T const * /*const*/() const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	template<typename T>
	struct Converter<T*,T const*const>
	{
		Converter(T* t):m_t(t){}
		operator T const * /*const*/() const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	template<typename T>
	struct Converter<T*,T*>
	{
		Converter(T* t):m_t(t){}
		operator T* () const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	
	template<typename T>
	struct Converter<T,T>
	{
		Converter(T& t):m_t(t){}
		operator T& () const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T& m_t;
	};
	template<typename T>
	struct Converter<T,T&>
	{
		Converter(T& t):m_t(t){}
		operator T& () const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T& m_t;
	};
	template<typename T>
	struct Converter<T,T*&>
	{
		Converter(T& t):m_t(&t){}
		operator T*& ()
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	template<typename T>
	struct Converter<T,T const&>
	{
		Converter(T& t):m_t(t){}
		operator T const& () const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T& m_t;
	};
	
	template<typename T>
	struct Converter<T*,T *const>
	{
		Converter(T* t):m_t(t){}
		operator T * () const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	template<typename T>
	struct Converter<T const*,T const*&>
	{
		Converter(T const*& t):m_t(t){}//added ref
		operator T const*&()
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T const*& m_t;//added ref
	};
	
	
	template<typename T>
	struct Converter<T,T const>
	{
		Converter(T& t):m_t(t){}
		operator T () const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T const & m_t;
	};
	
	template<typename T>
	struct Converter<T,T const*>
	{
		Converter(T & t):m_t(&t){}
		operator T const*&()
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T const* m_t;
	};
	template<typename T>
	struct Converter<T,T const *const>
	{
		Converter(T& t):m_t(&t){}
		operator T*const &() const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		T* m_t;
	};
	
	
	///////////////////////////////////////////////////////////////////////////////
	///  Specialisation for C style strings
	///	This removes const.
	///	The cast has to happen somewhere if a function want to take a none
	///	modifiable string as char* tut tut but it happerns.
	///////////////////////////////////////////////////////////////////////////////
	template<>
	struct Converter<char const*,char *>
	{
		Converter(char const* & t):m_t((char*)t){}
		operator char * () const
		{
			return m_t;
		}
		Converter& operator =(Converter const &);
		Converter(Converter const &);
		char * m_t;
	};
		
	}

}

/** \endcond */

#endif
