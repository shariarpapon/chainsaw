#pragma once
enum class GeneralTokenType
{
	seq_identifier,
	seq_delimiter,
	seq_number,
	seq_commentValue,
	ind_commentStart,
	ind_statementEnd,
	ind_accessor,
	ind_scopeStart,
	ind_scopeEnd,
	k_terminate,
	k_unexpected,
};
