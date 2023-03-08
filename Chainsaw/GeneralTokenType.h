#pragma once

namespace chainsaw {
	namespace core
	{
		enum class GeneralTokenType
		{
			s_identifier,
			s_delimiter,
			s_comment,
			s_number,
			s_statementEnd,
			s_accessor,
			s_scopeStart,
			s_scopeEnd,
			k_terminate,
			k_unexpected,
		};
	}
}