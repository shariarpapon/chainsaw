#include <iostream>
#include "GeneralUtils.h"

std::string getTestRawCode()
{
	return "1 base() while{ do if(x = y) > variable } end; var method function[] #this is comment#\0";
};

int main() {

	std::cout << getTestRawCode().c_str() << std::endl;
}


