#pragma once
#include <typeinfo>
#include "Token.h"
#include "TokenTypes.h"

static const std::string BLOCK_START_TOKEN_VALUE = "*BLOCK_START*";
static const std::string BLOCK_END_TOKEN_VALUE = "*BLOCK_END*";
static const std::string UNEXPECTED_TOKEN_VALUE = "*UNEXPECTED*";

class Lexer
{
public:
	inline Lexer(const char* source)
	{
		m_source = source;
		m_currBkIndex = 0;
	}
	inline static void printTokensStrRep(std::vector<Token*>& _tokens)
	{
		int i = 0;
		for (Token* token : _tokens)
		{
			++i;
			std::cout << "[TK-" + std::to_string(i) + "] " + token->getStringRep() << std::endl;
		}
	}			
	inline static void expandBlockTokens(std::vector<Token*>& _tokens)
	{
		std::vector<Token*> _expandedTokens;
		for (Token* orgTokenPtr : _tokens)
		{
			BlockToken* bkTokenPtr = dynamic_cast<BlockToken*>(orgTokenPtr);
			if (bkTokenPtr)
			{
				expandBlockTokensRecursively(_expandedTokens, bkTokenPtr);
			}
			else 
			{
				_expandedTokens.push_back(orgTokenPtr);
			}
		};
		_tokens.clear();
		_tokens = _expandedTokens;
	}
	inline static void expandBlockTokensRecursively(std::vector<Token*>& _expTokens, BlockToken* _bkTokenPtr)
	{
		for (Token* tokenPtr : _bkTokenPtr->getBlockTokens())
		{
			BlockToken* nwBkTokenPtr = dynamic_cast<BlockToken*>(tokenPtr);
			if (nwBkTokenPtr)
			{
				expandBlockTokensRecursively(_expTokens, nwBkTokenPtr);
			}
			else 
			{
				Token* nwToken = new Token(*tokenPtr);
				_expTokens.push_back(nwToken);
			}
		}
	}

	//Will analyze the source assigned in the constructor; starting from the current character address
	std::vector<Token*> analyze();
	void parseDelimiters();
	void parseUnexpected(std::string& _tokenValue);
	void parseIdentifiers(std::string& _tokenValue);
	void parseNumbers(std::string& _tokenValue);
	void parseComment(GeneralTokenType& _gTokenType, std::string& _tokenValue);
	void parseRegularToken(std::vector<Token*>& _tokens, GeneralTokenType& _gTokenType, std::string& _tokenValue);
	void parseBlock(std::vector<Token*>& _tokens, GeneralTokenType& _gTokenType, GeneralTokenType _bkTokenType, GeneralTokenType _bkeTokenType);

private:
	int m_currBkIndex;
	const char* m_source;

	std::vector<Token*> analyzeBlock(GeneralTokenType& _gTokenType, GeneralTokenType _bkeToken);
	inline GeneralTokenType getCurrGTokenType(char c)
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
		case 'v': case 'w': case 'x': case 'y': case 'z': case '_':
			return seq_identifier;
		case '0': case '1': case '2': case '3': case '4': case '5': case '6':
		case '7': case '8': case '9': case '.':
			return seq_number;
		case ' ': case '\n': case '\r': case '\t': case '\f': case '\v':
			return seq_delimiter;
		case '#':
			return ind_commentStart;

		case '+': case '-': case '*': case '/': case '%': case '&': case '<':
		case '>': case '=': case '|': case '!': case ':': case '?': case '^':
			return ind_operatorDelim;
		case ';':
			return ind_statementEnd;
		case ',':
			return ind_accessor;

		case '"':
			return enc_string;

		case '{':
			return bks_scope;
		case '}':
			return bke_scope;
		case '(': 
			return bks_expression;
		case ')': 
			return bke_expression;

		case '\0':
			return k_terminate;
		default:
			return k_unexpected;
		}
	}
	inline void addToken(std::vector<Token*>& _tokens, GeneralTokenType gTokenType, std::string tokenValue)
	{
		Token* token = new Token(gTokenType, tokenValue);
		_tokens.push_back(token);
	}
	inline void nextValue()
	{
		++m_source;
	}
	inline char getValue()
	{
		return *m_source;
	}
	inline bool isValidDelimiter(char c)
	{
		switch (c)
		{
		case ' ': case '\n': case '\r': case '\t': case '\f': case '\v':
			return true;
		default:
			return false;
		}
	}
	inline bool isValidIdentifier(char c)
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
		case 'v': case 'w': case 'x': case 'y': case 'z': case '_':

		case '0': case '1': case '2': case '3': case '4': case '5': case '6':
		case '7': case '8': case '9':
			return true;
		default:
			return false;
		}
	}
	inline bool isValidNumber(char c, bool& hasDecimalPoint)
	{
		switch (c)
		{
		case '0': case '1': case '2': case '3': case '4': case '5': case '6':
		case '7': case '8': case '9': 
			return true;
		case '.':
			if (hasDecimalPoint == true) return false;
			else 
			{
				hasDecimalPoint = true;
				return true;
			}
		default:
			return false;
		}
	}
	inline bool isEndOfComment(char c)
	{
		return c == '\n' || c == '\v' || c == '\r' || c == '\0' || c == '#';
	}
	inline bool isNullTerminator(char c)
	{
		if (c == '\0') return true;
		else return false;
	}
};
