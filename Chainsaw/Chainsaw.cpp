#include <iostream>
#include <vector>
#include <string>
#include "GeneralUtils.h"
#include "Lexer.h"

using namespace chainsaw::utils;

int main() {
	const char* source = "variable 12030 (variablex) { . //this is a comment";
	Lexer lexer(source);
	lexer.analyze();
	std::vector<Token> tokens = lexer.getAnalyzedToken();
	for (Token t : tokens) 
	{
		log_msg(t.getStringRep());
	}
}


