#include <File.hpp>

string openFile(const string& folder, const string& path){
    ifstream inputFile;
    inputFile.open((folder + path).c_str());

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

void replace_string(string& input, const string& pattern_in, const string& pattern_out){
    size_t pos = 0;

    while ((pos = input.find(pattern_in, pos)) != std::string::npos) {
        input.replace(pos, pattern_in.length(), pattern_out);
        pos += pattern_out.length();
    }
}