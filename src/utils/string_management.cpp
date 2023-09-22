#include "utils.hpp"

#include "debug.hpp"

string readFileIntoString(const string& path){
    ifstream input_file;
	input_file.open(path.c_str());
    if (!input_file.is_open()) {
		DEBUG_ERROR_ << "Failed to open file: " << path;
        return "error";
    }
    string res = string(
		std::istreambuf_iterator<char>(input_file),
		std::istreambuf_iterator<char>()
	);
    input_file.close();
    return res;
}

void replace_string(string& input, const string& pattern_in, const string& pattern_out){
    size_t pos = 0;

    while ((pos = input.find(pattern_in, pos)) != std::string::npos) {
        input.replace(pos, pattern_in.length(), pattern_out);
        pos += pattern_out.length();
    }
}

vector<string> split(const string& s, const string& delimiter){
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

vector<string> splitFirst(const string& s, const string& delimiter){
    vector<string> tokens;
    string::size_type pos = s.find(delimiter);

    if (pos != string::npos) {
        tokens.push_back(s.substr(0, pos));
        tokens.push_back(s.substr(pos + delimiter.length()));
    } else {
        // If delimiter not found, return the whole string as a single token
        tokens.push_back(s);
    }

    return tokens;
}

vector<string> splitStringByWhitespace(const string& input) {
	stringstream ss(input);
	vector<string> words;
	string word;

	while (ss >> word) {
		words.push_back(word);
	}

	return words;
}

// getline add \r at the end of a line :/ so this function removes it
bool removeCarriageReturn(string& line){
    // Check if the last character is a carriage return and remove it if present
    if (!line.empty() && line[line.length() - 1] == '\r') {
        line.erase(line.length() - 1);
    }
    return true;
}

u_int32_t stringToNumber(const string& str) {
    u_int32_t number;
    stringstream iss(str);

    if (!(iss >> number)) {
        return 0;
    }

    return number;
}

string numberToString(u_int32_t number) {
    stringstream oss;
    oss << number;
    return oss.str();
}

bool isPositiveInteger(const string& str) {
    if (str.empty()) {
        return false;
    }
    
    for (string::const_iterator it = str.begin(); it != str.end(); ++it) {
        if (!std::isdigit(*it)) {
            // cout << "X " << str << endl;
            return false;
        }
    }
    // cout << "V " << str << endl;
    return true;
}

bool startsWith(const string& input, const string& prefix) {
    // Check if the input string is shorter than the prefix
    if (input.length() < prefix.length()) {
        return false;
    }

    // Compare the first characters of input and prefix
    for (size_t i = 0; i < prefix.length(); ++i) {
        if (input[i] != prefix[i]) {
            return false;
        }
    }

    return true;
}