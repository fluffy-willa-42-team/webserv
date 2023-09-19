#include "file_parsing.hpp"

e_status parseline(ifstream& file, string& line, vector<string>& line_split, e_status& status, u_int32_t& index){
	if (!getline(file, line)){
		status = S_END;
		return S_END;
	}
	
	index++;

	// Remove Comments
	u_int64_t found = line.find_first_of(';');
	if (found != std::string::npos){
		line = line.substr(0, found);
	}

	if (line.size() == 0){
		status = S_PASS;
		return S_PASS;
	}

	if (line_split.size() > 0){
		line_split.clear();
	}
	
	line_split = splitStringByWhitespace(line);

	if (line_split.size() == 0){
		status = S_PASS;
		return S_PASS;
	}

	if (line_split.size() == 1 && line_split[0] == PARSING_GROUP_CLOSING){
		status = S_STOP;
		return S_STOP;
	}

	status = S_CONTINUE;
	return S_CONTINUE;
}