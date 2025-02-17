#include "Preprocessor.hpp"
#include "FileNode.hpp"

int main(int argc, char const *argv[])
{ 
	if(argc < 2)
	{
		std::cout << "Usage: ./main [input file]\n";
		exit(0);
	};

	FileNode fn(argv[1]);
	fn.read_file();
	fn.print(); 
	fn.include_files();

	return 0;
}