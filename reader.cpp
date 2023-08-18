#include "reader.h"
#include "utils.h"
#include "workspace.h"
#include <filesystem>

#define NULL_OUT_ERR_TEXT "the path of the directory for output of the result is not specified. Use the -O[path] parameter to specify this path or the -wc flag to output to the current directory."
#define NULL_RULE_ERR_TEXT "the path to the file containing the translation rules is not specified. Use the -R[path] parameter to specify this path, or the -rc flag to search for a file in the current directory."
#define NULL_FILE_ERR_TEXT "files for translation are not specified."
#define UNIDENTIFIED_FLAG "unidentified flag or parameter."
#define NOT_FOUND_FILES "the necessary files were not found."
#define UNCORRECT_TYPE_OUT "the -i and -s flags cannot be used at the same time."
#define RULE_FILE_NAME "rules"

namespace fs = std::filesystem;

void reader::read_command(int argc, char const *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		std::string temp(argv[i]);
		if (temp[0] == '-')
		{
			if (temp[1] == 'O')
			{
				workspace::out_path = std::string(temp, 2);
				workspace::out_path.append("/");
				continue;
			}
			if (temp[1] == 'R')
			{
				workspace::rules_path = std::string(temp, 2);
				continue;
			}
			if (temp[2] == 'c')
			{
				if (temp[1] == 'w')
				{
					utils::set_bit(workspace::flags, WC_FLAG);
					continue;
				}
				if (temp[1] == 'r')
				{
					utils::set_bit(workspace::flags, RC_FLAG);
					continue;
				}
			}
			if (temp[1] == 'f')
			{
				utils::set_bit(workspace::flags, F_FLAG);
				continue;
			}
			if (temp[1] == 'i')
			{
				utils::set_bit(workspace::flags, INT_FLAG);
				continue;
			}
			if (temp[1] == 's')
			{
				utils::set_bit(workspace::flags, SHORT_FLAG);
				continue;
			}
			utils::write_error(UNIDENTIFIED_FLAG);
		}
		else
		{
			workspace::paths.push_back(temp);
		}
	}

	if (workspace::out_path.length() == 0 && not WC_FLAG_VALUE)
		utils::write_error(NULL_OUT_ERR_TEXT);

	if (workspace::rules_path.length() == 0 && not RC_FLAG_VALUE)
		utils::write_error(NULL_RULE_ERR_TEXT);

	if (workspace::paths.size() == 0 && not F_FLAG_VALUE)
		utils::write_error(NULL_FILE_ERR_TEXT);
	
	if (I_FLAG_VALUE && S_FLAG_VALUE)
		utils::write_error(UNCORRECT_TYPE_OUT);
}

void reader::read_current_dir_files()
{
	if (utils::get_bit_value(workspace::flags, RC_FLAG))
	{
		for (const auto &entry : fs::directory_iterator("./"))
		{
			std::string entr = entry.path();
			if (!entr.compare(std::string("./").append(RULE_FILE_NAME)))
			{
				std::string temp = entry.path();
				temp.erase(0, 2);
				workspace::rules_path = temp;
				continue;
			}
			if (F_FLAG_VALUE && entr.find(".mnemonic") != std::string::npos)
			{
				workspace::paths.push_back(entr);
			}
		}
	}
	
	if (workspace::paths.size() == 0 
			|| workspace::rules_path.length() == 0)
		utils::write_error(NOT_FOUND_FILES);
	
	workspace::rules.read_from_file(workspace::rules_path);
}
