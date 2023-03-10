#pragma once
#include "Token.h"
#include "TokenTypes.h"

namespace chainsaw {
	namespace core {

		static const std::string SOURCE_FILE_EXTENSION = ".saw";
		
		class Lexer
		{
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
			void parseDelimiters();
			void parseUnexpected(std::string& _tokenValue);
			void parseIdentifiers(std::string& _tokenValue);
			void parseNumbers(std::string& _tokenValue);
			void parseComment(GeneralTokenType& _gTokenType, std::string& _tokenValue);
			void parseRegularToken(std::string& _tokenValue);

		private:
			std::vector<Token> m_tokens;
			const char* m_source;

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
					return GeneralTokenType::seq_identifier;
				case '0': case '1': case '2': case '3': case '4': case '5': case '6':
				case '7': case '8': case '9': case '.':
					return GeneralTokenType::seq_number;
				case ' ': case '\n': case '\r': case '\t': case '\f': case '\v':
					return GeneralTokenType::seq_delimiter;
				case '#':
					return GeneralTokenType::ind_commentStart;

				case '+': case '-': case '*': case '/': case '%': case '&': case '<':
				case '>': case '=': case '|': case '!': case ':':
					return GeneralTokenType::ind_operatorDelim;
				case ';':
					return GeneralTokenType::ind_statementEnd;
				case ',':
					return GeneralTokenType::ind_accessor;

				case '"':
					return GeneralTokenType::enc_string;

				case '{':
					return GeneralTokenType::bks_scope;
				case '}':
					return GeneralTokenType::bke_scope;
				case '(': 
					return GeneralTokenType::bks_expression;
				case ')': 
					return GeneralTokenType::bke_expression;

				case '\0':
					return GeneralTokenType::k_terminate;
				default:
					return GeneralTokenType::k_unexpected;
				}
			}
			inline void addToken(GeneralTokenType gTokenType, std::string tokenValue)
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
				return c == '\n' || c == '\v' || c == '\r' || c == '\0';
			}
			inline bool isNullTerminator(char c)
			{
				if (c == '\0') return true;
				else return false;
			}
		};

	}
}
