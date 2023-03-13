#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include "Lexer.h"

std::vector<Token*> Lexer::analyze()
{
	std::vector<Token*> _tokens;
	std::string _tokenValue = "";
	GeneralTokenType _gTokenType = GeneralTokenType::k_unexpected;

	while (!isNullTerminator(getValue()))
	{
		//initialize token type and token value for the current character
		_gTokenType = getCurrGTokenType(getValue());
		_tokenValue.clear();

		switch (_gTokenType)
		{
		case seq_delimiter:
		{
			parseDelimiters();
			continue;
		}
		case k_unexpected:
		{
			parseUnexpected(_tokenValue);
			break;
		}
		case seq_identifier:
		{
			parseIdentifiers(_tokenValue);
			break;
		}
		case seq_number:
		{
			parseNumbers(_tokenValue);
			break;
		}
		case ind_commentStart:
		{
			parseComment(_gTokenType, _tokenValue);
			break;
		}
		default:
		{
			parseRegularToken(_tokens, _gTokenType, _tokenValue);
			continue;
		}
		}
		addToken(_tokens, _gTokenType, _tokenValue);
	}
	return _tokens;
}
std::vector<Token*> Lexer::analyzeBlock(GeneralTokenType& _gTokenType, GeneralTokenType _bkeToken)
	{
		std::vector<Token*> _tokens;
		std::string _tokenValue = "";

		addToken(_tokens, getCurrGTokenType(getValue()), BLOCK_START_TOKEN_VALUE);
		nextValue();

		while (!isNullTerminator(getValue()))
		{
			//initialize token type and token value for the current character
			_gTokenType = getCurrGTokenType(getValue());

			if (_gTokenType == _bkeToken)
			{
				break;
			}

			_tokenValue.clear();

			switch (_gTokenType)
			{
			case seq_delimiter:
			{
				parseDelimiters();
				continue;
			}
			case k_unexpected:
			{
				parseUnexpected(_tokenValue);
				break;
			}
			case seq_identifier:
			{
				parseIdentifiers(_tokenValue);
				break;
			}
			case seq_number:
			{
				parseNumbers(_tokenValue);
				break;
			}
			case ind_commentStart:
			{
				parseComment(_gTokenType, _tokenValue);
				break;
			}
			default:
			{
				parseRegularToken(_tokens, _gTokenType, _tokenValue);
				continue;
			}
			}

			addToken(_tokens, _gTokenType, _tokenValue);
		}

		addToken(_tokens, getCurrGTokenType(getValue()), BLOCK_END_TOKEN_VALUE);
		return _tokens;
	}

void Lexer::parseDelimiters() 
{
	while (isWhiteSpace(getValue()))
	{
		nextValue();
	}
}
void Lexer::parseUnexpected(std::string& _tokenValue)
{
	_tokenValue = UNEXPECTED_TOKEN_VALUE;
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
	nextValue();
	_gTokenType = GeneralTokenType::seq_commentValue;
	while (!isEndOfComment(getValue()))
	{
		_tokenValue.push_back(getValue());
		nextValue();
	}
	nextValue();
}
void Lexer::parseRegularToken(std::vector<Token*>& _tokens, GeneralTokenType& _gTokenType, std::string& _tokenValue)
{
	_gTokenType = getCurrGTokenType(getValue());
	if (_gTokenType == bks_scope) 
	{
		parseBlock(_tokens, _gTokenType, bk_scope, bke_scope);
	}
	else if (_gTokenType == bks_expression) 
	{
		parseBlock(_tokens,_gTokenType, bk_expression, bke_expression);
	}
	else if(_gTokenType != bke_expression && _gTokenType != bke_scope)
	{
		_tokenValue.push_back(getValue());
		addToken(_tokens, _gTokenType, _tokenValue);
		nextValue();
	}
}
void Lexer::parseBlock(std::vector<Token*>& _tokens, GeneralTokenType& _gTokenType, GeneralTokenType _bkTokenType, GeneralTokenType _bkeTokenType) 
{
	std::vector<Token*> bkTokens = analyzeBlock(_gTokenType, _bkeTokenType);
	BlockToken* bkTokenPtr = new BlockToken(m_currBkIndex, _bkTokenType, bkTokens);
	_tokens.push_back(bkTokenPtr);
	nextValue();
	++m_currBkIndex;
}

