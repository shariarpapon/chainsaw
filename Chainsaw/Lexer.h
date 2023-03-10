#pragma once
#include "Token.h"

namespace chainsaw {
	namespace core {

		static const std::string SOURCE_FILE_EXTENSION = ".saw";
		
		class Lexer
		{
			struct Scope;

		public:
			inline Lexer(const char* source)
			{
				m_source = source;
			}
			inline static bool isSourceFileExtensionValid(std::string extension)
			{
				return extension == SOURCE_FILE_EXTENSION;
			}
			inline std::vector<Token> getAnalyzedTokens()
			{
				return m_tokens;
			}

			void analyze();

		private:
			std::vector<Token> m_tokens;
			const char* m_source;

			inline Token::GeneralTokenType getCurrGTokenType(char c)
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
					return Token::GeneralTokenType::seq_identifier;
				case '0': case '1': case '2': case '3': case '4': case '5': case '6':
				case '7': case '8': case '9': case '.':
					return Token::GeneralTokenType::seq_number;
				case ' ': case '\n': case '\r': case '\t': case '\f': case '\v':
					return Token::GeneralTokenType::seq_delimiter;
				case '/':
					return Token::GeneralTokenType::seq_commentStart;
				case '{':
					return Token::GeneralTokenType::ind_scopeStart;
				case '}':
					return Token::GeneralTokenType::ind_scopeEnd;
				case ';':
					return Token::GeneralTokenType::ind_statementEnd;
				case ',':
					return Token::GeneralTokenType::ind_accessor;
				case '\0':
					return Token::GeneralTokenType::k_terminate;
				default:
					return Token::GeneralTokenType::k_unexpected;
				}
			}
			inline void addToken(Token::GeneralTokenType gTokenType, std::string tokenValue)
			{
				m_tokens.push_back(Token::Token(gTokenType, tokenValue));
			}
			inline void nextValue()
			{
				++m_source;
			}
			inline char getValue()
			{
				return *m_source;
			}
			inline bool isDelimiter(char c)
			{
				switch (c)
				{
				case ' ': case '\n': case '\r': case '\t': case '\f': case '\v':
					return true;
				default:
					return false;
				}
			}
			inline bool isIdentifier(char c)
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
			inline bool isNumber(char c, bool& hasDecimalPoint)
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
			inline bool isCommentEnd(char c)
			{
				return c == '\n' || c == '\v' || c == '\r' || c == '\0';
			}
			inline bool isTerminated(char c)
			{
				if (c == '\0') return true;
				else return false;
			}

		};

	}
}
