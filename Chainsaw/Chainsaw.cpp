#include <iostream>
#include <vector>
#include "GeneralUtils.h"
#include "ChainsawLexer.h"
#include "ChainsawToken.h"

std::string getTestRawCode()
{
	return "1 base() while{ do if(x = y) > variable } end; var method function[] //this is comment.\n bool(x < 23412)";
};

int main() {
	std::string rawStr = getTestRawCode();
	const char* ptr_raw = rawStr.c_str();
	chainsaw::core::ChainsawLexer chainsawLexer(ptr_raw);
	std::vector<chainsaw::core::ChainsawToken> tokens = chainsawLexer.tokenize();
	for (chainsaw::core::ChainsawToken token : tokens)
	{
		std::cout << token.get_str_rep() << std::endl;
	}
}


