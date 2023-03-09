#pragma once
#include "GeneralTokenType.h"

static const std::string SOURCE_FILE_EXTENSION = ".saw";

struct Token
{
public:
	Token(GeneralTokenType gTokenType, std::string tokenValue)
	{
		this->gTokenType = gTokenType;
		this->tokenValue = tokenValue;
	}

	std::string getStringRep()
	{
		return "( " + std::to_string(static_cast<int>(gTokenType)) + " , " + tokenValue + " )";
	}
private:
	GeneralTokenType gTokenType;
	std::string tokenValue;
};

class Lexer
{
public:
	Lexer(const char* source);
	void analyze();
	std::vector<Token> getAnalyzedToken();

	inline static bool isSourceFileExtensionValid(std::string extension) 
	{
		return extension == SOURCE_FILE_EXTENSION;
	}

private:
	const char* m_source;

	void nextValue();
	void previousValue();

	GeneralTokenType getGeneralTokenType(char charValue);
	char getValue();
	bool isDelimiter(char c);
	bool isCommentEnd(char c);
	bool isTerminated(char c);
	bool isIdentifier(char c);
	bool isNumber(char c);
};
