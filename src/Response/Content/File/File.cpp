#include <File.hpp>

FileContent::FileContent(const string& path) : Content(path){
	cout << PURPLE << "Constructing a File Content" << RESET << endl;
	data = "[File Content]";
	type = "text/plain";
}

FileContent::~FileContent(){}

string FileContent::toString() const {
	stringstream ss;
	
	ss	<< "Content-Length: " << data.length();

	if (data.length() > 0)
	ss	<< endl << "Content-Type: " << type << endl
		<< endl
		<< data;
	return ss.str();
}


