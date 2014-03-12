#ifndef __BASECONV_H
#define __BASECONV_H

#include <string>
#include <sstream>
#include <cmath>
#include <cctype>

namespace bsc
{
	class BaseConverter
	{
	private:
		static double getFraction(double num);
		static unsigned int getInteger(double num);

	public:
		static std::string convertToBase(double source, unsigned int targetBase, unsigned int fractionBits = 8);
		static double convertFromBase(std::string input, unsigned int baseFrom);
	};
}

#endif