#include <fstream>
#include <string>
//#include <sstream>

inline void add_file_header(std::ofstream& f,std::string const& file_name)
{
	f<<"///////////////////////////////////////////////////////////////////////////////\n"
		<<"///  @file " <<file_name.c_str() <<"\n"
		<<"///  @remarks Warning this file was generated, edits to it will not persist if \n"
		<<"///  the file is regenerated.\n"
		<<"///  @author Liam Devine\n"
		<<"///  @email\n"
		<<"///  See http://www.liamdevine.co.uk for contact details.\n"
		<<"///  @licence \n"
		<<"///  This work is licenced under a Creative Commons Licence. \\n \n"
		<<"///  see: \\n \n"
		<<"///  http://creativecommons.org/licenses/by-nc-sa/3.0/ \n"
		<<"///  and: \\n \n"
		<<"///  http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode \\n \n"
		<<"///  For more details.\n"
		<<"///////////////////////////////////////////////////////////////////////////////\n";
}
inline void include_header(std::ofstream & f,std::string const& header)
{
	f<<"#\tinclude \""<<header <<"\"\n";
}
inline void include_guard_top(std::ofstream& f,std::string const& name)
{
	f<<"#ifndef " <<name.c_str() <<"\n"
		<<"#\tdefine " <<name.c_str() <<"\n\n";
}
inline void include_guard_bottom(std::ofstream& f)
{
	//inserts new line at end for standard compliance
	f<<"\n\n#endif \n";
}