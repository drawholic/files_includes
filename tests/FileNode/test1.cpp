#include "FileNode.hpp"
#include <cassert>
#include <cstdio>


void test()
{
	const char* filename = "./tests/hello.cpp";
	FileNode f(filename);

	assert(strcmp(filename, f.get_filename()) == 0);

	f.read_file();

	assert(f.get_line_num() == 5);
};

int main()
{
	test();

	return 0;
};
