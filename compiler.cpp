#include "compiler.h"
#include "utils.h"
#include "workspace.h"
#include <fstream>

void compiler::translate_source(const std::string path)
{
	std::string source = utils::get_file_contents(path.c_str());
	utils::trim_string(source);
	std::vector<std::string> mnemonic = utils::explode_string(" ", source);
	
	std::string filename = path.substr(path.rfind("/") + 1);
	if (filename.find(".") != std::string::npos)
	{
		filename.erase(filename.find("."));
	}
	filename.insert(0, workspace::out_path);
	filename.append(".code");
	
	std::ofstream out(filename.c_str());
	
	for (int i = 0; i < mnemonic.size(); i++)
		{
			if (workspace::rules.contains(mnemonic[i]))
			{
				int code = workspace::rules.get_property(mnemonic[i]);
				char flag = I_FLAG_VALUE << 1 | S_FLAG_VALUE;
				if (flag >= 2)
				{
					out << (char) (code >> 24);
					out << (char) (code >> 16);
				}
				if (flag > 0)
				{
					out << (char) (code >> 8);
				}
				out << (char) code;
			}
		}
	out.close();
}
