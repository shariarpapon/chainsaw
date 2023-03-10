#include <iostream>
#include <vector>
#include <string>
#include "GeneralUtils.h"
#include "Lexer.h"

using namespace chainsaw::utils;
using namespace chainsaw::core;

int main() {
	std::string sourceStr = "var newSourceTest = true;"
							"NewScope { array = y }"
							"#break comment with new line\n"
		                    "expression {nested (block2)} "
							"#force break comment#"
							"process.execute(true)";

	Lexer lexer(sourceStr.c_str());

	std::cout << "========== Compact Tokens ==========" << std::endl;
	std::vector<Token*> _tokens = lexer.analyze();
	Lexer::printTokensStrRep(_tokens);

	std::cout << "\n========== Expanded Tokens ==========" << std::endl;
	Lexer::expandBlockTokens(_tokens);
	Lexer::printTokensStrRep(_tokens);

	//deallocate token memory
	deall_token_vector(_tokens);
}

