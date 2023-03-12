#pragma once

enum GeneralTokenType
{
	seq_delimiter = 0,
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
	bk_scope,
	bks_expression,
	bke_expression,
	bk_expression,

	k_terminate,
	k_unexpected,
};
