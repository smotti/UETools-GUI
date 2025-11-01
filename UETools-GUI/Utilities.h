#pragma once
#include <Windows.h>
#include <string>
#include <algorithm>






namespace Utilities
{
	class Clipboard
	{
	public:
		static bool Set(const std::string& str);
	};






	class String
	{
	public:
		static std::string ToLowerCase(const std::string& str);
		static std::string ToUpperCase(const std::string& str);
	};
};

