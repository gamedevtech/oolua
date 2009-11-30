#ifndef COMMON_CPPUNIT_HEADERS_H_
#	define COMMON_CPPUNIT_HEADERS_H_

#	if defined _MSC_VER
#		pragma warning(push)
//		constant conditional (in cppunit) on the no throw do while loop vs2008
#		pragma warning( disable : 4127 )
//		warning C4512 assignment operator could not be generated (in cppunit)
#		pragma warning( disable : 4512 )
//		warning C4511:  copy constructor could not be generated (in cppunit)vs2003
#		pragma warning( disable : 4511 )
#	endif
///  \addtogroup cppunit_tests
///  @{
///  \see tests.xml
///  @}

#		include "cppunit/TestCase.h"
#		include "cppunit/extensions/HelperMacros.h"
#		include "cppunit/ui/text/TestRunner.h"
#		include "cppunit/XmlOutputter.h"
#		include "cppunit/TestResultCollector.h"
#		include "cppunit/CompilerOutputter.h"
#		ifdef _MSC_VER
#			include "cppunit/config/SourcePrefix.h"
#		endif

#define LVD_NOCOPY(TYPE) \
	TYPE(TYPE const&); \
	TYPE& operator = (TYPE const&);

#	if defined _MSC_VER
#	    pragma warning(pop)
#   endif

#endif
