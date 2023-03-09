#include <iostream>
#include "GeneralUtils.h"

void chainsaw::utils::log_msg(std::string msg)
{
	std::cout << msg << std::endl;
}

std::string chainsaw::utils::read_string()
{
	std::string input;
	std::cin >> input;
	return input;
}

std::string chainsaw::utils::prompt_read_string(std::string prompt)
{
	log_msg(prompt);
	return read_string();
}


