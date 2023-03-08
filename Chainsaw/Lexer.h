#pragma once
#include "GeneralTokenType.h"

namespace chainsaw {
	namespace core
	{
		static const std::string SOURCE_FILE_EXTENSION = ".saw";

		class Lexer
		{
		public:
			Lexer(const char* source);
			void analyze();

			inline static bool isSourceFileExtensionValid(std::string extension) 
			{
				return extension == SOURCE_FILE_EXTENSION;
			}

		private:
			const char* source;

			void shiftPointer();
			char getValue() const;
			GeneralTokenType getGeneralTokenType(char charValue) const;

			bool isDelimiter(char c) const;
			bool isCommentEnd(char c) const;
			bool isTerminated(char c) const;
		};
	}
}