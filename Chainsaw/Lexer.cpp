#include <iostream>
#include <vector>
#include <string>
#include "Lexer.h"

using namespace chainsaw::core;

class TokenBlock
{
public:
	TokenBlock(int scopeIndex, std::vector<Token> scopeTokens)
	{
		m_scopeIndex = scopeIndex;
		m_scopeTokens = scopeTokens;
	}
	int getScopeIndex()
	{
		return m_scopeIndex;
	}
	std::vector<Token> getScopeTokens()
	{
		return m_scopeTokens;
	}
	std::string getStringRep()
	{
		return "Scope Index [" + std::to_string(m_scopeIndex) + "]";
	}
private:
	int m_scopeIndex;
	std::vector<Token> m_scopeTokens;
};

void Lexer::analyze()
{
	std::string _tokenValue = "";
	GeneralTokenType _gTokenType = GeneralTokenType::k_unexpected;

	while (!isNullTerminator(getValue()))
	{
		//initialize token type and token value for the current character
		_gTokenType = getCurrGTokenType(getValue());
		_tokenValue.clear();

		switch (_gTokenType) 
		{
			case GeneralTokenType::seq_delimiter: 
			{
				parseDelimiters();
				continue;
			}
			case GeneralTokenType::k_unexpected: 
			{
				parseUnexpected(_tokenValue);
				break;
			}
			case GeneralTokenType::seq_identifier:
			{
				parseIdentifiers(_tokenValue);
				break;
			}
			case GeneralTokenType::seq_number: 
			{
				parseNumbers(_tokenValue);
				break;
			}
			case GeneralTokenType::ind_commentStart:
			{
				parseComment(_gTokenType, _tokenValue);
				break;
			}
			default: 
			{
				parseRegularToken(_tokenValue);
				break;
			}
		}

		addToken(_gTokenType, _tokenValue);
	}
}

void Lexer::parseDelimiters() 
{
	while (isValidDelimiter(getValue()))
	{
		nextValue();
	}
}
void Lexer::parseUnexpected(std::string& _tokenValue)
{
	_tokenValue = "UNEXPECTED";
	nextValue();
}
void Lexer::parseIdentifiers(std::string& _tokenValue)
{
	while (isValidIdentifier(getValue()))
	{
		_tokenValue.push_back(getValue());
		nextValue();
	}
}
void Lexer::parseNumbers(std::string& _tokenValue) 
{
	bool _hasDecimalPoint = false;
	while (isValidNumber(getValue(), _hasDecimalPoint))
	{
		_tokenValue.push_back(getValue());
		nextValue();
	}
}
void Lexer::parseComment(GeneralTokenType& _gTokenType, std::string& _tokenValue) 
{
	_gTokenType = getCurrGTokenType(getValue());
	if (_gTokenType != GeneralTokenType::ind_commentStart)
	{
		_tokenValue.push_back('#');
		_gTokenType = GeneralTokenType::seq_identifier;
	}
	else
	{
		_gTokenType = GeneralTokenType::seq_commentValue;
		nextValue();
		while (!isEndOfComment(getValue()))
		{
			_tokenValue.push_back(getValue());
			nextValue();
		}
	}
}
void Lexer::parseRegularToken(std::string& _tokenValue)
{
	_tokenValue.push_back(getValue());
	nextValue();
}


