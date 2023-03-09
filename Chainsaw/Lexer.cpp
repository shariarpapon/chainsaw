#include <iostream>
#include <vector>
#include <string>
#include "GeneralTokenType.h"
#include "Lexer.h"
#include "GeneralUtils.h"

using namespace chainsaw::utils;

const char* m_source;
std::vector<Token> m_tokens;

Lexer::Lexer(const char* source)
{
		m_source = source;
}

std::vector<Token> Lexer::getAnalyzedToken()
{
	return m_tokens;
}

void Lexer::analyze()
{
	std::string _tokenValue = "";
	GeneralTokenType _gTokenType = GeneralTokenType::k_unexpected;

	while (!isTerminated(getValue())) 
	{
		//initialize token type and token value for the current character
		_gTokenType = getGeneralTokenType(getValue());
		_tokenValue.clear();

		if (_gTokenType == GeneralTokenType::k_unexpected)
		{
			//special case premature return
			_tokenValue = "UNEXPECTED";
			m_tokens.push_back(Token::Token(_gTokenType, _tokenValue));
			nextValue();
			continue;
		}
		else if (_gTokenType == GeneralTokenType::seq_delimiter) 
		{
			//process the first non-delim character in the next iteration (prevents adding delim characters to the list of tokens).
			while (isDelimiter(getValue())) 
			{
				nextValue();
			}
			continue;
		}
		else if (_gTokenType == GeneralTokenType::seq_identifier)
		{
			//process identifier-sequence
			while (isIdentifier(getValue())) 
			{
				_tokenValue.push_back(getValue());
				nextValue();
			}
			m_tokens.push_back(Token::Token(_gTokenType, _tokenValue));
		}
		else if (_gTokenType == GeneralTokenType::seq_number)
		{
			//process number-sequence
			while (isNumber(getValue())) 
			{
				_tokenValue.push_back(getValue());
				nextValue();
			}
			m_tokens.push_back(Token::Token(_gTokenType, _tokenValue));
		}
		else if (_gTokenType == GeneralTokenType::ind_commentStart)
		{
			//process comment tokens
			nextValue();
			_gTokenType = getGeneralTokenType(getValue());
			if (_gTokenType != GeneralTokenType::ind_commentStart)
			{
				_tokenValue.push_back('/');
				m_tokens.push_back(Token::Token(GeneralTokenType::seq_identifier, _tokenValue));
				continue;
			}
			else 
			{
				nextValue();
				while (!isCommentEnd(getValue())) 
				{
					_tokenValue.push_back(getValue());
					nextValue();
				}
				m_tokens.push_back(Token::Token(GeneralTokenType::seq_commentValue, _tokenValue));
			}
		}
		else 
		{
			_tokenValue.push_back(getValue());
			m_tokens.push_back(Token::Token(_gTokenType, _tokenValue));
			nextValue();
		}
	}
}

void Lexer::nextValue()
{
	++m_source;
}
void Lexer::previousValue()
{
	--m_source;
}

GeneralTokenType Lexer::getGeneralTokenType(char charValue)
{
	switch (charValue)
	{
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
	case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
	case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
	case 'V': case 'W': case 'X': case 'Y': case 'Z':
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
	case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
	case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
	case 'v': case 'w': case 'x': case 'y': case 'z':
		return GeneralTokenType::seq_identifier;
	case '0': case '1': case '2': case '3': case '4': case '5': case '6':
	case '7': case '8': case '9':
		return GeneralTokenType::seq_number;
	case ' ': case '\n': case '\r': case '\t': case '\f': case '\v':
		return GeneralTokenType::seq_delimiter;
	case '/':
		return GeneralTokenType::ind_commentStart;
	case '{':
		return GeneralTokenType::ind_scopeStart;
	case '}':
		return GeneralTokenType::ind_scopeEnd;
	case '.':
		return GeneralTokenType::ind_statementEnd;
	case ',':
		return GeneralTokenType::ind_accessor;
	case '\0':
		return GeneralTokenType::k_terminate;
	default:
		return GeneralTokenType::k_unexpected;
	}
}
char Lexer::getValue() 
{
	return *m_source;
}
bool Lexer::isDelimiter(char c) 
{
	switch (c) 
	{
		case ' ': case '\n': case '\r': case '\t': case '\f': case '\v':
			return true;
		default: 
			return false;
	}
}
bool Lexer::isCommentEnd(char c)  
{
	return c == '\n' || c == '\v' || c =='\r' || c == '\0';
}
bool Lexer::isTerminated(char c)  
{
	if (c == '\0') return true;
	else return false;
}
bool Lexer::isIdentifier(char c)  
{
	switch (c) 
	{
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
	case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
	case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
	case 'V': case 'W': case 'X': case 'Y': case 'Z':
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
	case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
	case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
	case 'v': case 'w': case 'x': case 'y': case 'z':
		return true;
	default:
		return false;
	}
}
bool Lexer::isNumber(char c)  
{
	switch (c) 
	{
	case '0': case '1': case '2': case '3': case '4': case '5': case '6':
	case '7': case '8': case '9': 
		return true;
	default: 
		return false;
	}
}
