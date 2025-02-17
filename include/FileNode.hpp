#ifndef FILE_NODE_HPP
#define FILE_NODE_HPP

#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>
#include <regex>

const std::regex include_expression_regex("^#include (<(.*)>|\"(.*)\")$");

const unsigned BUFFER_SIZE = 256;

class FileNode
{
	std::ifstream input_file;
	std::ofstream output_file;

	char* filename;
	unsigned line_num;
	std::vector<FileNode*> children;
	char* buffer;

public:
	FileNode();
	FileNode(char*);
	FileNode(const char*);
	FileNode(const char*, unsigned);


	void set_filename(const char*);

	char* get_filename() const;
	unsigned get_line_num() const;

	void read_file();
	void include_files();

	const char* get_include_filename();
	bool check_include_statement();
	void add_child(const char*);
	void add_child(FileNode*);

	void print();
};

#endif