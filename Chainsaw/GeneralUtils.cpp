#include <iostream>
#include <vector>
#include "GeneralUtils.h"
#include "Token.h"

void chainsaw::utils::deall_token_vector(std::vector<Token*>& vec)
{
    for (Token* ptr : vec)
    {
        if (ptr != nullptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }
    vec.clear();
}

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



