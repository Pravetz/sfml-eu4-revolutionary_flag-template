#include "../include/readfile.hpp"

std::vector<char> read_file(const std::string &path){
	std::vector<char> raw_src;
	
	std::ifstream _file;
	_file.open(path.c_str(), std::fstream::binary);
	if(_file){
		_file.seekg(0, _file.end);
		size_t srclen = _file.tellg();
		_file.seekg(0, _file.beg);
		raw_src.resize(srclen);
		_file.clear();
		_file.read(raw_src.data(), srclen);
	}
	else{
		raw_src.clear();
		std::cout<<"File in path \'"<<path<<"\' doesn't exist."<<std::endl;
	}
	
	
	return raw_src;
}
