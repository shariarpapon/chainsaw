#pragma once
#include <iostream>
#include "TokenType.h"

namespace chainsaw {
	namespace core {
		class ChainsawToken {
		public:
			ChainsawToken(const char* raw, TokenType tokenType);
		};
	};
};



