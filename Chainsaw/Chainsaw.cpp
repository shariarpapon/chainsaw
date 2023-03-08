#include <iostream>
#include <vector>
#include <string>
#include "GeneralUtils.h"
#include "Lexer.h"

using namespace chainsaw::core;
using namespace chainsaw::utils;

const char* getTestSource()
{
	return "1 base() while{ do if(x = y) > variable } end; var method function[] //this is comment.\n bool(x < 23412)";
};

int main() {
	Lexer lexer();
	bool a1 = Lexer::isSourceFileExtensionValid(".raaw");
	bool a2 = Lexer::isSourceFileExtensionValid(".saw");
	
	log_msg(std::to_string(a1));
	log_msg(std::to_string(a2));
}


