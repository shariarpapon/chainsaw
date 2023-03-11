#include <iostream>
#include <vector>
#include <string>
#include "GeneralUtils.h"
#include "Lexer.h"

using namespace chainsaw::utils;
using namespace chainsaw::core;

int main() 
{
	const char* source = 
		"bool value = x > 10.2 ? true : false;"
		"scope { #this is seperate block of code# y = 20 }"
		"#comment: break comment with new line\n"
		"#comment: force break comment with a second `hash`#"
		"#comment: code block nesting example# "
		"{"
			"#comment: inside first nested block#"
			"int x = 1;"
			"int y = x * 234.5081"
			"{"
				"#comment: inside second nested block# "
				"if (condition_expression) minute = sec / 60"
				"{"
					"#comment: inside second adjecent block#"
					"return getSomeValue == true;"
				"}"
			"}"
		"}";

	Lexer lexer(source);

	std::cout << "========== Compact Tokens ==========" << std::endl;
	std::vector<Token*> _tokens = lexer.analyze();
	Lexer::printTokensStrRep(_tokens);

	std::cout << "\n========== Expanded Tokens ==========" << std::endl;
	Lexer::expandBlockTokens(_tokens);
	Lexer::printTokensStrRep(_tokens);

	//deallocate token memory
	deall_token_vector(_tokens);
}

