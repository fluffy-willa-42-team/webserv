#include "Error.hpp"

string readFileIntoString(const string& path);
void replace_string(string& input, const string& pattern_in, const string& pattern_out);

Error::Error()
: code(0), description(""), message("")
{}

Error::Error(u_int32_t code, string description)
: code(code), description(description)
{}

Error::Error(u_int32_t code, string description, string message)
: code(code), description(description), message(message)
{}

Error::~Error(){}

const Error& Error::operator=(const Error& other){
	this->code = other.code;
	this->message = other.message;
	this->description = other.description;
	return *this;
}

const string Error::http(){
	string error_file = readFileIntoString("./errors/error.html");
	stringstream code_str; code_str << code;
	replace_string(error_file, "{{code}}", code_str.str());
	replace_string(error_file, "{{error_desc}}", description);
	if (message.length() > 0){
		replace_string(error_file, "{{error_message}}", message);
	}
	else {
		replace_string(error_file, "{{error_message}}", "");
	}

	map<string, string> header;
	header["Content-Type"] = "text/html";
	header["Content-Length"] = error_file.length();

	stringstream ss;
	ss << PROTOCOL << " " << code << " " << description << endl;
	for (map<string, string>::iterator ite = header.begin(); ite != header.end(); ite++){
		ss << ite->first << ": " << ite->second << endl;
	}
	ss << endl;
	ss << error_file;
	
	cout << ss.str();

	return ss.str();
}
