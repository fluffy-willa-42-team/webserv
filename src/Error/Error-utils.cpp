#include "webserv.hpp"

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