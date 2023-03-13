#include "Lexer.h"
#include "Token.h"

extern "C" __declspec(dllexport) struct CToken 
{
public:
	int tokenId;
	char* tokenValue;
	char* tokenStrRep;

	CToken() 
	{
		tokenId = 16;
		tokenValue = (char*)UNEXPECTED_TOKEN_VALUE.c_str();
		tokenStrRep = (char*)UNEXPECTED_TOKEN_VALUE.c_str();
	}

	CToken(int _tokenId, char* _tokenValue, char* _tokenStrRep) 
	{
		tokenId = _tokenId;
		tokenValue = _tokenValue;
		tokenStrRep = _tokenStrRep;
	}
};
extern "C" __declspec(dllexport) CToken** Tokenize(const char* source, bool keepCompact, int* size) 
{
	Lexer lexer(source);
	std::vector<Token*> tokens = lexer.analyze();

	if (!keepCompact) {
		Lexer::expandBlockTokens(tokens);
	}

	*size = static_cast<int>(tokens.size());
	CToken** cTokens = new CToken*[*size];
	CToken** baseTokenPtr = cTokens;

	for (Token* tokenPtr : tokens) 
	{
		int tokenId = static_cast<int>(tokenPtr->getGTokenType());
		std::string tokenValue = (*tokenPtr).getTokenValue();
		std::string tokenStrRep = (*tokenPtr).getStringRep();

		char* tokenValue_cpy = new char[tokenValue.length() + 1];
		char* tokenStrRep_cpy = new char[tokenStrRep.length() + 1];

		strcpy_s(tokenValue_cpy, tokenValue.length() + 1, tokenValue.c_str());
		strcpy_s(tokenStrRep_cpy, tokenStrRep.length() + 1, tokenStrRep.c_str());

		CToken* cToken = new CToken(tokenId, tokenValue_cpy, tokenStrRep_cpy);
		*cTokens = cToken;
		++cTokens;
	}
	return baseTokenPtr;
}