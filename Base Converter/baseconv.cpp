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

	std::string BaseConverter::convertToBase(double source, unsigned int targetBase, unsigned int fractionBits)
	{
		if (targetBase == 0 || source == 0.0)
		{
			throw std::exception();
		}

		std::stringstream output;
		std::string num;

		unsigned int integer = BaseConverter::getInteger(source);

		while (integer != 0)
		{
			unsigned int remainder = integer % targetBase;
			integer /= targetBase;

			num.push_back(remainder + '0');
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

			num.push_back(remainder + '0');
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

	double BaseConverter::convertFromBase(std::string input, unsigned int baseFrom)
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
			char token = tolower(input[i]);
			unsigned int digit;

			if (isdigit(token))
			{
				digit = token - '0';
			}
			else if (isalpha(token) && token >= 'a' && token <= 'z')
			{
				digit = (token - 'a') + 10;
			}

			result += digit * pow(baseFrom, position - i - 1);
		}

		// fractional part
		for (size_t i = position + 1; i < input.size(); ++i)
		{
			char token = tolower(input[i]);
			unsigned int digit;

			if (isdigit(token))
			{
				digit = token - '0';
			}
			else if (isalpha(token) && token >= 'a' && token <= 'z')
			{
				digit = (token - 'a') + 10;
			}

			result += digit * (1.0 / pow(baseFrom, i - position));
		}

		return result;
	}
}