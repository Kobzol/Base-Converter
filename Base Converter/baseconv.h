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
		static char getNumberChar(unsigned int num);
		static unsigned int getNumberDigit(char num);

		static double convertFromBase(std::string input, unsigned int sourceBase);

	public:
		static std::string convertToBase(std::string input, unsigned int sourceBase, unsigned int targetBase, unsigned int fractionBits = 8);
	};
}

#endif