#pragma once
#include <iostream>

namespace chainsaw {
	namespace utils {

		void log_msg(std::string);
		std::string prompt_read_string(std::string prompt);
		std::string read_string();
	};
};
