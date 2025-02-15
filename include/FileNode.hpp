#ifndef FILE_NODE_HPP
#define FILE_NODE_HPP

#include <vector>
#include <fstream>

class FileNode
{

	std::ifstream input_file;
	std::ofstream output_file;
	
	char* filename;
	unsigned line_num;
	std::vector<FileNode*> files_to_include;

public:
	FileNode();
	
};

#endif