#include "response.hpp"

string get_file_res(const string& file_path, bool download){
	ifstream input_file;
	input_file.open(file_path.c_str());
	if (!input_file.is_open()) {
		if 		(input_file.fail() && input_file.bad())		{ return error(403, "file fail"); }
		else if (input_file.fail() && !input_file.bad())	{ return error(404, "file fail"); }
		else 												{ return error(500, "file fail"); }
	}
	string res_file_body = string(
		std::istreambuf_iterator<char>(input_file),
		std::istreambuf_iterator<char>()
	);
	input_file.close();
	map<string, string> header;
	header[HEADER_CONTENT_TYPE] = "text/html";
	if (download){
		cout << file_path << endl;
		const string filename = file_path.substr(file_path.find_last_of('/') + 1);
		header[HEADER_DOWNLOAD] = "attachment; filename=\"" + filename + "\"";
	}
	return get_response(200, header, res_file_body);
}