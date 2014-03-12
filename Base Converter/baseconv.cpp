#include "baseconv.h"

namespace bsc
{
	double BaseConverter::getFraction(double num)
	{
		if ((int)num > 0)
		{
			return fmod(num, (int)num);
		}
		else return num;
	}

	unsigned int BaseConverter::getInteger(double num)
	{
		return (unsigned int)num;
	}

	char BaseConverter::getNumberChar(unsigned int num)
	{
		if (num >= 0 && num <= 9)
		{
			return num + '0';
		}
		else if (num >= 10 && num <= 15)
		{
			return 'A' + (num - 10);
		}
		else return 'X';
	}

	unsigned int BaseConverter::getNumberDigit(char num)
	{
		unsigned int digit;

		num = tolower(num);

		if (num >= '0' && num <= '9')
		{
			digit = num - '0';
		}
		else if (num >= 'a' && num <= 'z')
		{
			digit = (num - 'a') + 10;
		}

		return digit;
	}

	std::string BaseConverter::convertToBase(std::string input, unsigned int sourceBase, unsigned int targetBase, unsigned int fractionBits)
	{
		if (targetBase == 0 || sourceBase == 0)
		{
			throw std::exception();
		}

		double source = BaseConverter::convertFromBase(input, sourceBase);

		std::stringstream output;
		std::string num;

		unsigned int integer = BaseConverter::getInteger(source);

		while (integer != 0)
		{
			unsigned int remainder = integer % targetBase;
			integer /= targetBase;

			num.push_back(BaseConverter::getNumberChar(remainder));
		}

		for (int i = num.size() - 1; i >= 0; --i)
		{
			output << num[i];
		}

		output << '.';

		num.clear();

		double fraction = BaseConverter::getFraction(source);

		bool hasFraction = false;
		for (unsigned int i = 0; i < fractionBits; ++i)
		{
			unsigned int remainder;

			fraction *= targetBase;

			remainder = BaseConverter::getInteger(fraction);
			fraction = BaseConverter::getFraction(fraction);

			if (!hasFraction && remainder > 0)
			{
				hasFraction = true;
			}

			num.push_back(BaseConverter::getNumberChar(remainder));
		}

		for (size_t i = 0; i < num.size(); ++i)
		{
			output << num[i];
		}

		std::string result = output.str();

		if (!hasFraction)
		{
			result = result.substr(0, result.find("."));
		}

		return result;
	}

	double BaseConverter::convertFromBase(std::string input, unsigned int sourceBase)
	{
		double result = 0.0;

		size_t position = input.find(".");

		if (position == std::string::npos)
		{
			position = input.size();
		}

		// integer part
		for (size_t i = 0; i < position; ++i)
		{
			char token = input[i];
			unsigned int digit = BaseConverter::getNumberDigit(token);

			result += digit * pow(sourceBase, position - i - 1);
		}

		// fractional part
		for (size_t i = position + 1; i < input.size(); ++i)
		{
			char token = input[i];
			unsigned int digit = BaseConverter::getNumberDigit(token);

			result += digit * (1.0 / pow(sourceBase, i - position));
		}

		return result;
	}
}