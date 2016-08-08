#pragma once

#define WJP_DEBUG_ON
//#define WJP_UNIT_TEST

#include <exception>

namespace wjp {
	struct Position {
		Position() :Position(0, 0) {}
		Position(int x) : Position(x, 50) {}
		Position(int x, int y) :x(x), y(y) {}
		int											x;
		int											y;
	};

	class FileException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "File loading failed!";
		}
	};


}
