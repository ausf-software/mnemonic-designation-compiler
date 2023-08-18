#include <string>
#include <vector>
#include "utils.h"

#pragma once

#define WC_FLAG 0
#define RC_FLAG 1
#define F_FLAG 2
#define SHORT_FLAG 3
#define INT_FLAG 4

#define I_FLAG_VALUE utils::get_bit_value(workspace::flags, INT_FLAG)
#define S_FLAG_VALUE utils::get_bit_value(workspace::flags, SHORT_FLAG)
#define F_FLAG_VALUE utils::get_bit_value(workspace::flags, F_FLAG)
#define WC_FLAG_VALUE utils::get_bit_value(workspace::flags, WC_FLAG)
#define RC_FLAG_VALUE utils::get_bit_value(workspace::flags, RC_FLAG)

namespace workspace
{
	extern std::vector<std::string> paths;
	extern std::string out_path;
	extern std::string rules_path;
	extern utils::Properties rules;
	extern char flags;
}
