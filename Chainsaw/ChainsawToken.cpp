#include <iostream>
#include "TokenType.h"

namespace chainsaw {
	namespace core {
		class ChainsawToken {
		public:
			const char* raw;
			TokenType tokenType;
			ChainsawToken(const char* p_raw, TokenType p_tokenType)
			{
				raw = p_raw;
				tokenType = p_tokenType;
			}
		};

	};
};