#pragma once
#include <iostream>
#include <string>
#include "TokenTypes.h"

namespace chainsaw {
	namespace core {

		class Token
		{
		public:
			inline Token() {};
			inline Token(GeneralTokenType gTokenType, std::string tokenValue)
			{
				m_gTokenType = gTokenType;
				m_tokenValue = tokenValue;
			}
			inline virtual std::string getStringRep()
			{ 
				return "| " + std::to_string(m_gTokenType) + " ~ " + m_tokenValue + " |";
			}
		protected:
			GeneralTokenType m_gTokenType;
			std::string m_tokenValue;
		};

		class BlockToken : Token 
		{
		public:
			inline BlockToken() 
			{
				m_blockTokens = std::vector<Token>();
			}
			void addTokenToBlock(Token token) 
			{
				m_blockTokens.push_back(token);
			}
		private:
			std::vector<Token> m_blockTokens;
		};
	}
}