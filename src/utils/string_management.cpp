#include "utils.hpp"

string readFileIntoString(const string& path) {
    ifstream input_file;
	input_file.open(path.c_str());
    if (!input_file.is_open()) {
		cout << "Failed to open file" << endl;
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

vector<string> split(const string& s, const string& delimiter) {
    vector<string> tokens;
    string::size_type start = 0;
    string::size_type end;

    while ((end = s.find(delimiter, start)) != string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
    }

    tokens.push_back(s.substr(start));
    return tokens;
}
