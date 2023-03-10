#pragma once
#include <iostream>
#include <vector>
#include "Token.h"
using namespace chainsaw::core;

namespace chainsaw {
	namespace utils {

		void deall_token_vector(std::vector<Token*>& vec);
		void log_msg(std::string);
		std::string prompt_read_string(std::string prompt);
		std::string read_string();
	};
};
