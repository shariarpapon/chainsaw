#pragma once
#include <iostream>
#include "TokenType.h"

namespace chainsaw {
	namespace core {
		class ChainsawToken {
		public:
			ChainsawToken(std::string l_rawStr, TokenType l_tokenType);
			std::string get_str_rep();
		};
	};
};



