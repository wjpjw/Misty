#pragma once

/*Everything else in namespace wjp.*/

#define WJP_DEBUG_ON
//#define WJP_UNIT_TEST

#include <exception>

namespace wjp {
	class FileException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "File loading failed!";
		}
	};

	static inline const char* font1() { return "fonts/Marker Felt.ttf"; }
	static inline const char* font2() { return "fonts/A Damn Mess.ttf"; }
	static inline const char* font3() { return "fonts/Abberancy.ttf"; }
	static inline const char* font4() { return "fonts/Abduction.ttf"; }
	static inline const char* font5() { return "fonts/American Typewriter.ttf"; }
	static inline const char* font6() { return "fonts/arial.ttf"; }
	static inline const char* font7() { return "fonts/Paint Boy"; }

}
