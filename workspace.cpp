#include "workspace.h"

std::vector<std::string> workspace::paths;
std::string workspace::out_path = "";
std::string workspace::rules_path = "";
utils::Properties workspace::rules;
char workspace::flags = 0;
