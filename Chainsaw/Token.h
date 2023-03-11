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
			inline GeneralTokenType getGTokenType() 
			{
				return m_gTokenType;
			}
			inline virtual std::string getStringRep()
			{ 
				return "Type<" + std::to_string(m_gTokenType) + "> |" + m_tokenValue + "|";
			}
		protected:
			GeneralTokenType m_gTokenType;
			std::string m_tokenValue;
		};

		class BlockToken : public Token
		{
		public:
			inline BlockToken(int bkIndex, GeneralTokenType bkTokenType, std::vector<Token*> bkTokens)
			{
				m_bkIndex = bkIndex;
				m_gTokenType = bkTokenType;
				m_bkTokensPtr = bkTokens;
			}
			inline int getScopeIndex()
			{
				return m_bkIndex;
			}
			inline std::vector<Token*> getBlockTokens()
			{
				return m_bkTokensPtr;
			}
			inline std::string getStringRep() override
			{
				return "<Bk> |" + std::to_string(m_bkIndex) + "|";
			}
		private:
			int m_bkIndex;
			std::vector<Token*> m_bkTokensPtr;
		};
	}
}