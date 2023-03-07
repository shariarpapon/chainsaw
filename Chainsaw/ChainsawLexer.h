#pragma once
#include "ChainsawToken.h"
#include <vector>

namespace chainsaw {
	namespace core {
		class ChainsawLexer {
		public:
			ChainsawLexer(const char* raw);
			std::vector<ChainsawToken> tokenize();

		private:
			TokenType token_type();
			char peek();
			char next();
			bool is_identifier();
			bool is_space();
			bool is_number();
			bool is_comment();
		};
	};
};

