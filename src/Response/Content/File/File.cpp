#include <File.hpp>

FileContent::FileContent(const string& path) : Content(path){
	cout << PURPLE << "Constructing a File Content" << RESET << endl;
	data = "[File Content]";
	length = data.length();
	type = "text/plain";
}

FileContent::~FileContent(){}

string FileContent::toString() const {
	stringstream ss;
	
	ss	<< "Content-Length: " << length;

	if (length > 0)
	ss	<< endl << "Content-Type: " << type << endl
		<< endl
		<< data;
	return ss.str();
}


