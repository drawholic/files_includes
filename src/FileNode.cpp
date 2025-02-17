#include "FileNode.hpp"


FileNode::FileNode(){
	line_num = 0;
};

FileNode::FileNode(char * fname)
{
	line_num = 0;
	set_filename(fname);
};

FileNode::FileNode(const char* fname, unsigned line): line_num(line)
{
	set_filename(fname);
};

FileNode::FileNode(const char* fname)
{
	line_num = 0;
	set_filename(fname);
};

void FileNode::set_filename(const char* fname)
{
	unsigned length = strlen(fname);
	filename = new char[length];
	strcpy(filename, fname);
};

char* FileNode::get_filename() const
{
	return filename;
};

unsigned FileNode::get_line_num()const{
	return line_num;
};

void FileNode::read_file()
{
	input_file.open(filename);

	if(!input_file.is_open())
	{
		std::cerr << "Failure opening: " << get_filename() << std::endl;
		exit(EXIT_FAILURE);
	};

	buffer = new char[BUFFER_SIZE];

	const char *include_filename;
	
	FileNode* fn;
	while(input_file.getline(buffer, BUFFER_SIZE))
	{
		line_num++;
		include_filename = get_include_filename();
		if(include_filename)
		{
			fn = new FileNode(include_filename, line_num);
			children.push_back(fn);
		};
	};
	input_file.close();

	for(auto it : children)
	{
		it->read_file();
	};
};

void FileNode::include_files()
{
	std::ofstream out_f;
	std::ifstream in_f;

	std::string out_filename = std::string(filename) + ".temp";

	in_f.open(filename, std::fstream::in);
	if(!in_f.is_open())
	{
		std::cerr << "Failure opening" << filename << std::endl;
		exit(1);
	};

	out_f.open(out_filename, std::fstream::out);

	if(!out_f.is_open())
	{
		std::cerr << "Failure creating: " << out_filename << std::endl;
		in_f.close();
		exit(1);
	};

	unsigned current_line = 1;
	unsigned include_line;
	buffer = new char[BUFFER_SIZE];

	std::ifstream include_file;

	for(auto it = children.begin(); it != children.end(); it++)
	{
		include_line = (*it)->get_line_num();
 
		while(in_f.getline(buffer, BUFFER_SIZE) && current_line < include_line)
		{
			out_f.write(buffer, in_f.gcount());
			out_f.write("\n", 1);
			current_line++;
		};
		include_file.open((*it)->get_filename(), std::fstream::in);

		if(!include_file.is_open())
		{
			std::cerr << "Failure opening: " << (*it)->get_filename() << std::endl;
			in_f.close();
			out_f.close();
			exit(1);
		};

		while(include_file.getline(buffer, BUFFER_SIZE))
		{
			out_f.write(buffer, include_file.gcount());
			out_f.write("\n", 1);
		};
		current_line++;

		include_file.close();
	};

};

const char* FileNode::get_include_filename()
{
	std::cmatch cm;

	std::regex_match(buffer, cm, include_expression_regex);

	char* include_filename = 0;
	const char* match_string = 0;

	unsigned length;
	unsigned match_index;

	if(cm.length(3))
	{
		match_index = 3;
	}else if(cm.length(2))
	{
		match_index = 2; 
	}else{
		return include_filename;
	};
	
	length = cm.length(match_index);
	match_string = cm[match_index].str().c_str();
	
	include_filename = new char[length + 1];
	include_filename[length] = 0;

	strncpy(include_filename, match_string, length);

	return include_filename;
};

void FileNode::add_child(const char* name)
{
	FileNode* fn = new FileNode(name);
	add_child(fn);
};

void FileNode::add_child(FileNode* child)
{
	children.push_back(child);
};

void FileNode::print()
{
	std::cout << "Filename: "<< filename << ", Line: " << line_num << std::endl;

	if(!children.empty())
	{
		std::cout << "children: ";
		for(auto i : children)
		{
			std::cout << i->get_filename() << ", ";
		};
		std::cout << std::endl;

		for(auto i : children)
		{
			i->print();
		};
	};
	
};