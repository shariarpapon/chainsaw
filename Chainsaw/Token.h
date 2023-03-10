#pragma once
#include <iostream>
#include <string>
#include "Lexer.h";

namespace chainsaw {
	namespace core {

		struct Token
		{
			enum GeneralTokenType
			{
				seq_delimiter,
				seq_identifier,
				seq_number,
				seq_commentValue,
				seq_commentStart,
				ind_statementEnd,
				ind_accessor,
				ind_scopeStart,
				ind_scopeEnd,
				k_terminate,
				k_unexpected,
			};

		public:
			inline Token(GeneralTokenType gTokenType, std::string tokenValue)
			{
				this->gTokenType = gTokenType;
				this->tokenValue = tokenValue;
			}
			inline std::string getStringRep()
			{ 
				return "( " + std::to_string(gTokenType) + " , " + tokenValue + " )";
			}
		private:
			GeneralTokenType gTokenType;
			std::string tokenValue;
		};
	}
}