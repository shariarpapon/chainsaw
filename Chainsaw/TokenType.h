#pragma once
namespace chainsaw {
	namespace core {
		enum class TokenType {
			spcl_unexpected,
			spcl_identifier,
			spcl_comment,
			spcl_number,
			spcl_space,
			lft_paran,
			rgt_paran,
			lft_curly,
			rgt_curly,
			lft_sqrb,
			rgt_sqrb,
			less_thn,
			greater_thn,
			plus,
			minus,
			comma,
			dot,
			hash,
			colon,
			semi_cln,
			pipe,
			bwd_slash,
			fwd_slash,
			asterisk,
			sngl_quote,
			dbl_quote,
			equal,
			spcl_end_scope,
		};
	};
};
