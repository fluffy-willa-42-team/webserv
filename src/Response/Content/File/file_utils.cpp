#include <File.hpp>

string openFile(const string& folder, const string& path){
    ifstream inputFile;
    inputFile.open((folder + path).c_str());

    if (inputFile.is_open()) {
        stringstream buffer;
        buffer << inputFile.rdbuf();
        inputFile.close();
		return buffer.str();
    } else {
		throw FileContent::FileNotFound();
    }
}

void replace_string(string& input, const string& pattern_in, const string& pattern_out){
    size_t pos = 0;

    while ((pos = input.find(pattern_in, pos)) != std::string::npos) {
        input.replace(pos, pattern_in.length(), pattern_out);
        pos += pattern_out.length();
    }
}

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