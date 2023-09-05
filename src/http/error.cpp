#include "webserv.hpp"

string get_response(u_int32_t code, map<string, string> headers, string body);

map<u_int32_t, string>& get_codes_map();
static map<u_int32_t, string>& codes_map = get_codes_map();

string readFileIntoString(const string& path) {
    ifstream input_file;
	input_file.open(path.c_str());
    if (!input_file.is_open()) {
        return "";
    }
    return string(
		std::istreambuf_iterator<char>(input_file),
		std::istreambuf_iterator<char>()
	);
}

void replace_string(string& input, const string& pattern_in, const string& pattern_out){
    size_t pos = 0;

    while ((pos = input.find(pattern_in, pos)) != std::string::npos) {
        input.replace(pos, pattern_in.length(), pattern_out);
        pos += pattern_out.length();
    }
}

string error(u_int32_t code, const string& message){
	string error_file = readFileIntoString("./errors/error.html");
	stringstream code_str; code_str << code;
	replace_string(error_file, "{{code}}", code_str.str());
	replace_string(error_file, "{{error_desc}}", codes_map[code]);
	if (message.length() > 0){
		replace_string(error_file, "{{error_message}}", message);
	}
	else {
		replace_string(error_file, "{{error_message}}", "");
	}
	map<string, string> header;
	header["Content-Type"] = "text/html";

	return get_response(code, header, error_file);
}

