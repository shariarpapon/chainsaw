#include <iostream>
#include <string>
#include "TokenType.h"

namespace chainsaw {
	namespace core {

		struct ChainsawToken {

			std::string rawStr;
			TokenType tokenType;

			ChainsawToken(std::string l_rawStr, TokenType l_tokenType) {
				rawStr = l_rawStr;
				tokenType = l_tokenType;
			}

			std::string get_str_rep() {
				return "(" + rawStr + ")";
			}
		};

	};
};