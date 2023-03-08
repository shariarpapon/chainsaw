#include "GeneralTokenType.h"

namespace chainsaw {
	namespace core
	{
		class Lexer
		{
		public:
			Lexer(const char* source)
			{
				this->source = source;
			}

			void analyze()
			{
				while (!isTerminated(getValue())) 
				{
					if (isDelimiter(getValue())) shiftPointer();

					if (getGeneralTokenType(getValue()) == GeneralTokenType::s_identifier) 
					{

					}
				}
			}

		private:
			const char* source;

			void shiftPointer()
			{
				source++;
			}
			char getValue() const
			{
				return *source;
			}
			GeneralTokenType getGeneralTokenType(char charValue) const
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
					return GeneralTokenType::s_identifier;
				case '0': case '1': case '2': case '3': case '4': case '5': case '6':
				case '7': case '8': case '9':
					return GeneralTokenType::s_number;
				case '/':
					return GeneralTokenType::s_comment;
				case ' ': case '\n': case '\r': case '\t': case '\f': case '\v':
					return GeneralTokenType::s_delimiter;
				case '{':
					return GeneralTokenType::s_scopeStart;
				case '}':
					return GeneralTokenType::s_scopeEnd;
				case '.':
					return GeneralTokenType::s_statementEnd;
				case ',':
					return GeneralTokenType::s_accessor;
				case '\0':
					return GeneralTokenType::k_terminate;
				default:
					return GeneralTokenType::k_unexpected;
				}
			}
			bool isDelimiter(char c) const
			{
				switch (c) 
				{
					case ' ': case '\n': case '\r': case '\t': case '\f': case '\v':
						return true;
					default: 
						return false;
				}
			}
			bool isCommentEnd(char c) const 
			{
				return c == '\n' || c == '\v' || c =='\r';
			}
			bool isTerminated(char c) const 
			{
				if (c == '\0') return true;
				else return false;
			}
			bool isIdentifier(char c) const 
			{

			}

		};
	}
}
