#include <iostream>
#include <vector>
#include <string>
#include "GeneralUtils.h"
#include "Lexer.h"


using namespace chainsaw::utils;
using namespace chainsaw::core;

int main() {
	const char* source = "variable 1.2.030 (variablex): if(a = b) { 0.123 } #this is a comment\n double x = 91.02";
	Lexer lexer(source);
	lexer.analyze();
	for (Token t : lexer.getAnalyzedTokens())
	{
		log_msg(t.getStringRep());
	}
}


