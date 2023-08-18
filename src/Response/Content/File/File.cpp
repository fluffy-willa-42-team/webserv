#include <File.hpp>

string openFile(const string& folder, const string& path);
void replace_string(string& input, const string& pattern_in, const string& pattern_out);

string generate_error_page(int error_code, const Config& config, const string& message){
	string error_file = openFile("/home/willa/19/webserv/errors/", "/error.html");

	std::stringstream ss;
    ss << error_code;

	replace_string(error_file, "{{code}}", ss.str());
	replace_string(error_file, "{{error_desc}}", config.status_codes.at(error_code));
	if (message.length() > 0){
		replace_string(error_file, "{{error_message}}", message);
	}
	return error_file;
}

FileContent::FileContent(const string& path, const Config& config) : Content(path){
	cout << PURPLE << "Constructing a File Content" << RESET << endl;
	type = "text/html";

	(void) config;
	try
	{
		data = openFile("/home/willa/19/webserv/static/", path);
	}
	catch(const FileContent::FileNotFound& e)
	{
		std::stringstream ss;
		ss << path << " does not exist";
		data = generate_error_page(404, config, ss.str());
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


