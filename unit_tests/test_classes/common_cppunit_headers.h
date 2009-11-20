#ifndef COMMON_CPPUNIT_HEADERS_H_
#	define COMMON_CPPUNIT_HEADERS_H_

#	if defined _MSC_VER

//#		ifndef MSCV_COMPILER_WARNING_PUSHED
//#			define MSCV_COMPILER_WARNING_PUSHED
//#		endif
//		constant conditional (in cppunit) on the no throw do while loop vs2008
#		pragma warning( disable : 4127 )
#		pragma warning(push)
//		warning C4512 assignment operator could not be generated (in cppunit)
#		pragma warning( disable : 4512 )
//		warning C4511:  copy constructor could not be generated (in cppunit)vs2003
#		pragma warning( disable : 4511 )
//		constant conditional (in cppunit) on the no throw do while loop vs2008
//#		pragma warning( disable : 4127 )
#	endif
///  \addtogroup cppunit_tests
///  @{
///  \see tests.xml
///  @}

#	ifdef USING_CPPUNIT
#		include "cppunit/TestCase.h"
#		include "cppunit/extensions/HelperMacros.h"
#		include "cppunit/ui/text/TestRunner.h"
#		include "cppunit/XmlOutputter.h"
#		include "cppunit/TestResultCollector.h"
#		include "cppunit/CompilerOutputter.h"
#		ifdef _MSC_VER
#			include "cppunit/config/SourcePrefix.h"
#		endif
#	else
#	include <stdexcept>

#		if defined LVD_NO_CHECKING
#			define CPPUNIT_ASSERT(x)
#			define CPPUNIT_ASSERT_EQUAL(x,y)
#			define CPPUNIT_TEST_SUITE(X)
#			define CPPUNIT_TEST_SUITE_END()
#			define CPPUNIT_TEST(X) X();
#			define CPPUNIT_ASSERT_NO_THROW(x) x
#			define CPPUNIT_TEST_SUITE_REGISTRATION(x)
#			define CPPUNIT_ASSERT_THROW_MESSAGE(a,b,c)
#		else
#			include <cassert>
#			define CPPUNIT_ASSERT(x) assert(x)
#			define CPPUNIT_ASSERT_EQUAL(x,y) assert(x == y)
#			define CPPUNIT_TEST_SUITE(X)
#			define CPPUNIT_TEST_SUITE_END()
#			define CPPUNIT_TEST(X) X();
#			define CPPUNIT_ASSERT_NO_THROW(x)\
			try\
			{\
				x;\
			}\
			catch (...)\
			{\
				assert(0);\
			}
#			define CPPUNIT_ASSERT_THROW_MESSAGE(a,b,c)\
			b;


#		endif
#	endif

#define LVD_NOCOPY(TYPE) \
	TYPE(TYPE const&); \
	TYPE& operator = (TYPE const&);

#	if defined _MSC_VER
//#if defined MSCV_COMPILER_WARNING_PUSHED
//#	undef MSCV_COMPILER_WARNING_PUSHED
#	pragma warning(pop)
#endif

#endif
