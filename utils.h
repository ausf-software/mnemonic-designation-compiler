#include <map>
#include <vector>
#include <string>
#pragma once

namespace utils
{
	std::string get_file_contents(const char* filename);
	std::vector<std::string> explode_string(const std::string &delimiter, const std::string &str);
	void trim_string(std::string& data);
	void write_error(const std::string text);

	int get_bit_value(char _char, int n);
	void set_bit(char& _char, int n);

	class Properties
	{
		private:
			std::map<std::string, int> key_pair;
		public:
			Properties();
			int contains(const std::string key);
			void read_from_file(const std::string _file_path);
			int get_property(const std::string _property);
			std::string to_string();
	};
}
