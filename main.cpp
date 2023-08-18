#include "reader.h"
#include "workspace.h"
#include "compiler.h"

int main(int argc, char const *argv[])
{
	reader::read_command(argc, argv);
	reader::read_current_dir_files();
	for (int i = 0; i < workspace::paths.size(); i++)
	{
		compiler::translate_source(workspace::paths[i]);
	}
	return 0;
}
