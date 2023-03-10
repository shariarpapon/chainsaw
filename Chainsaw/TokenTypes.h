#pragma once
namespace chainsaw {
	namespace core {
	
		enum GeneralTokenType
		{
			seq_delimiter,
			seq_identifier,
			seq_number,
			seq_commentValue,

			ind_commentStart,
			ind_statementEnd,
			ind_operatorDelim,
			ind_accessor,

			enc_string,

			bks_scope,
			bke_scope,
			bks_expression,
			bke_expression,

			k_terminate,
			k_unexpected,
		};

	}
}