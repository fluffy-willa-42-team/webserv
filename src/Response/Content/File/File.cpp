#include <File.hpp>

FileContent::FileContent(const string& path) : Content(path){
	cout << PURPLE << "Constructing a File Content" << RESET << endl;
}

FileContent::~FileContent(){}

string FileContent::toString() const {
	return "[File Content]";
}


