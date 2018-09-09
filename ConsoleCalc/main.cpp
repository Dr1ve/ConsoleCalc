#include <iostream>
#include <string>
#include "Expression.h"

int main(int argc, char **argv)
{
	std::string str;
	if (argc > 1)
	{
		for (int i = 1;i < argc; ++i)
		{
			str += argv[i];
		}
	}
	else
	{
		//str = "5+5*5";
		//str = "-1 + 5 - 3";
		//str = "-10 + (8 * 2.5) - (3 / 1,5)";
		str = "1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)";
		//str = "1.1 + 2.1 + abc";
	}
	str = "1+2/(5+1)";
	std::cout << "primer: " << str << std::endl;

	size_t bad_symbol = str.find_first_not_of("1234567890+-*/.,() ");
	if (bad_symbol != std::string::npos)
		std::cout << "bad sybmol" << std::endl;
	else
	{

		Context * cont = new Context();
		Expression * expr = cont->evaluate(str);
		std::cout << "otvet: " << expr->interpret() << std::endl;
	}

	return 0;
}
