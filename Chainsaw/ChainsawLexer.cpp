#include <iostream>
#include <vector>
#include "ChainsawToken.h"

namespace chainsaw {
	namespace core {

		class ChainsawLexer {

		private:
			const char* m_raw;

		public:
			ChainsawLexer(const char* raw) {
				m_raw = raw;
			};

			std::vector<ChainsawToken> tokenize() {

				std::vector<ChainsawToken> tokensVector;
				TokenType _type = token_type();
				std::string term;

				while (_type != TokenType::spcl_end_scope) {

					if (_type == TokenType::spcl_space) {
						while (is_space()) continue;
					}

					if (_type == TokenType::spcl_identifier) {
						term = "" + peek();
						while (is_identifier()) term += peek();
						tokensVector.push_back(ChainsawToken(term, TokenType::spcl_identifier));
						term.clear();
					}

					if (_type == TokenType::spcl_number) {
						term = "" + peek();
						while (is_number()) term += peek();
						tokensVector.push_back(ChainsawToken(term, TokenType::spcl_number));
						term.clear();
					}

					if (_type == TokenType::spcl_comment)
					{
						next();
						if (token_type() == TokenType::spcl_comment)
						{
							next();
							term = "" + peek();
							while (is_comment()) term += peek();
							tokensVector.push_back(ChainsawToken(term, TokenType::spcl_comment));
							term.clear();
						}
					}

					std::string term = "" + peek();
					tokensVector.push_back(ChainsawToken(term, token_type()));
					term.clear();

					next();
					_type = token_type();
				}
				return tokensVector;
			};

			TokenType token_type()
			{
				switch (peek())
				{
				case 'a': case 'b': case 'c':
				case 'd': case 'e': case 'f':
				case 'g': case 'h': case 'i':
				case 'j': case 'k': case 'l':
				case 'm': case 'n': case 'o':
				case 'p': case 'q': case 'r':
				case 's': case 't': case 'u':
				case 'v': case 'w': case 'x':
				case 'y': case 'z': case 'A':
				case 'B': case 'C': case 'D':
				case 'E': case 'F': case 'G':
				case 'H': case 'I': case 'J':
				case 'K': case 'L': case 'M':
				case 'N': case 'O': case 'P':
				case 'Q': case 'R': case 'S':
				case 'T': case 'U': case 'V':
				case 'W': case 'X': case 'Y':
				case 'Z': return TokenType::spcl_identifier;

				case '0': case '1': case '2':
				case '3': case '4': case '5':
				case '6': case '7': case '8':
				case '9':return TokenType::spcl_number;

				case '(': return TokenType::lft_paran;
				case ')': return TokenType::rgt_paran;
				case '[': return TokenType::lft_sqrb;
				case ']': return TokenType::rgt_sqrb;
				case '{': return TokenType::lft_curly;
				case '}': return TokenType::rgt_curly;
				case '<': return TokenType::less_thn;
				case '>': return TokenType::greater_thn;
				case '=': return TokenType::equal;
				case '+': return TokenType::plus;
				case '-': return TokenType::minus;
				case '*': return TokenType::asterisk;
				case '#': return TokenType::hash;
				case '.': return TokenType::dot;
				case ',': return TokenType::comma;
				case ':': return TokenType::colon;
				case ';': return TokenType::semi_cln;
				case '\'': return TokenType::sngl_quote;
				case '"': return TokenType::dbl_quote;
				case '/': return TokenType::spcl_comment;
				case '\\': return TokenType::bwd_slash;
				case '|': return TokenType::pipe;
				case '\0': return TokenType::spcl_end_scope;
				default: return TokenType::spcl_unexpected;
				}
			};
			char peek() {
				return *m_raw;
			};
			char next() {
				m_raw++;
				return peek();
			};

			//assumes the first character is identifier
			bool is_identifier() {
				next();
				return token_type() == TokenType::spcl_identifier;
			};

			bool is_space() {
				next();
				return token_type() == TokenType::spcl_space;
			};

			bool is_number() {
				next();
				return token_type() == TokenType::spcl_number;
			};

			bool is_comment() {
				next();
				return peek() != '\n' && peek() != '\0';
			};
		};

	};
};


