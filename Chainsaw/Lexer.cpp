#include <iostream>
#include <vector>
#include <string>
#include "Lexer.h"

using namespace chainsaw::core;

struct Lexer::Scope
{
public:
	Scope(int scopeIndex, std::vector<Token> scopeTokens)
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
	Token::GeneralTokenType _gTokenType = Token::GeneralTokenType::k_unexpected;

	while (!isTerminated(getValue()))
	{
		//initialize token type and token value for the current character
		_gTokenType = getCurrGTokenType(getValue());
		_tokenValue.clear();

		switch (_gTokenType) 
		{
			case Token::GeneralTokenType::seq_delimiter: 
			{
				while (isDelimiter(getValue()))
				{
					nextValue();
				}
				continue; 
			}
			case Token::GeneralTokenType::k_unexpected: 
			{
				_tokenValue = "UNEXPECTED";
				nextValue();
				break;
			}
			case Token::GeneralTokenType::seq_identifier:
			{
				while (isIdentifier(getValue()))
				{
					_tokenValue.push_back(getValue());
					nextValue();
				}
				break;
			}
			case Token::GeneralTokenType::seq_number: 
			{
				bool _hasDecimalPoint = false;
				while (isNumber(getValue(), _hasDecimalPoint))
				{
					_tokenValue.push_back(getValue());
					nextValue();
				}
				break;
			}
			case Token::GeneralTokenType::seq_commentStart:
			{
				_gTokenType = getCurrGTokenType(getValue());
				if (_gTokenType != Token::GeneralTokenType::seq_commentStart)
				{
					_tokenValue.push_back('/');
					_gTokenType = Token::GeneralTokenType::seq_identifier;
				}
				else
				{
					_gTokenType = Token::GeneralTokenType::seq_commentValue;
					nextValue();
					while (!isCommentEnd(getValue()))
					{
						_tokenValue.push_back(getValue());
						nextValue();
					}
				}
				break;
			}
			default: 
			{
				_tokenValue.push_back(getValue());
				nextValue();
			}
		}
		addToken(_gTokenType, _tokenValue);
	}
}

