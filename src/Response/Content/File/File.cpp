#include <File.hpp>

string openFile(const string& path){
    ifstream inputFile;
	string route = "/home/willa/19/webserv/static/";
    inputFile.open((route + path).c_str());

	cout << "path: " << path << endl;

    if (inputFile.is_open()) {
        stringstream buffer;
        buffer << inputFile.rdbuf();
        inputFile.close();
		return buffer.str();
    } else {
		throw FileContent::FileNotFound();
    }
}

FileContent::FileContent(const string& path) : Content(path){
	cout << PURPLE << "Constructing a File Content" << RESET << endl;
	type = "text/html";

	try
	{
		data = openFile(path);
	}
	catch(const FileContent::FileNotFound& e)
	{
		data = openFile("/error.html");
	}
}

FileContent::~FileContent(){}

string FileContent::toString() const {
	stringstream ss;
	
	ss	<< "Content-Length: " << data.length();

	if (data.length() > 0){
		ss	<< endl << "Content-Type: " << type << endl
			<< endl
			<< data;
	}
	return ss.str();
}


