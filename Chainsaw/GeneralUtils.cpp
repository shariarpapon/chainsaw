#include <iostream>

namespace chainsaw 
{
	namespace utils
	{
		void log_msg(std::string msg)
		{
			std::cout << msg << std::endl;
		}

		std::string read_string()
		{
			std::string input;
			std::cin >> input;
			return input;
		}

		std::string prompt_read_string(std::string prompt)
		{
			log_msg(prompt);
			return read_string();
		}
	};
}


