#include "utils.h"
#include <fstream>
#include <string>
#include <cerrno>
#include <iostream>

std::string utils::get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

std::vector<std::string> utils::explode_string(const std::string &delimiter, const std::string &str)
{
	std::vector<std::string> arr;

	int strleng = str.length();
	int delleng = delimiter.length();
	if (delleng == 0)
		return arr;

	int i = 0;
	int k = 0;

	while(i < strleng)
	{
		int j = 0;
		while (i + j < strleng && j < delleng && str[i+j] == delimiter[j])
			j++;

		if (j == delleng)//found delimiter
		{
			arr.push_back(str.substr(k, i-k));
			i += delleng;
			k = i;
		}
		else
		{
			i++;
		}
	}
	arr.push_back(str.substr(k, i-k));
	return arr;
}

void utils::trim_string(std::string& data)
{
	int _n, _t, _s;
	do
	{
		_n = data.find("\n");
		_t = data.find("\t");
		_s = data.find("  ");
		if (_n != std::string::npos) {
			data[_n] = ' ';
		}
		if (_t != std::string::npos) {
			data[_t] = ' ';
		}
		if (_s != std::string::npos) {
			data.erase(_s, 1);
		}
	} while (_n != std::string::npos 
				|| _t != std::string::npos 
				|| _s != std::string::npos);
	
	if (data.find("  ") == 0)
	{
		data.erase(0, 1);
	}
	if (data.find("  ") == data.length() - 1)
	{
		data.erase(data.length() - 1, 1);
	}
}

utils::Properties::Properties() {}

void utils::Properties::read_from_file(const std::string _file_path)
{
	std::string data = utils::get_file_contents(_file_path.c_str());
	std::vector<std::string> ar = utils::explode_string("\n", data);

	std::string temp;
	for (int i = 0; i < ar.size(); i++)
	{
		int selector = ar[i].find("=");
		if (selector != std::string::npos)
		{
			temp = ar[i].substr(0, selector);
			key_pair[temp] = std::stoi(ar[i].substr(selector + 1));
		}
	}
}

int utils::Properties::get_property(const std::string _property)
{
	return key_pair[_property];
}

int utils::Properties::contains(const std::string key)
{
	return key_pair.count(key);
}

std::string utils::Properties::to_string()
{
	std::string temp = "";
	for(std::map<std::string, int>::iterator it = key_pair.begin(); it != key_pair.end(); it++)
	{
		temp += it->first + " = " + std::to_string(it->second) + "\n";
	}
	return temp;
}

void utils::write_error(const std::string text)
{
	std::cerr << "Error: " << text << std::endl;
	exit(1);
}

int utils::get_bit_value(char _char, int n)
{
	return (_char >> n) & 1u;
}

void utils::set_bit(char& _char, int n)
{
	_char |= 1u << n;
}
