#include "response.hpp"

map<string, string> content_type;

void init_content_type(){
	content_type[".html"]	= "text/html";
	content_type[".css"]	= "text/css";
	content_type[".js"]		= "text/javascript";
	content_type[".json"]	= "application/json";
	content_type[".xml"]	= "application/xml";
	content_type[".pdf"]	= "application/pdf";
	content_type[".jpg"]	= "image/jpeg";
	content_type[".jpeg"]	= "image/jpeg";
	content_type[".png"]	= "image/png";
	content_type[".gif"]	= "image/gif";
	content_type[".mpeg"]	= "audio/mpeg";
	content_type[".wav"]	= "audio/wav";
	content_type[".ogg"]	= "audio/ogg";
	content_type[".mp4"]	= "video/mp4";
	content_type[".webm"]	= "video/webm";
}


string get_content_type(const string& filename){
	for (Headers::const_iterator ite = content_type.begin(); ite != content_type.end(); ite++){
		if (endsWith(filename, ite->first)){
			return ite->second;
		}
	}
	return "text/plain";
}


string get_file_res(const string& file_path, bool download){
	ifstream input_file;
	input_file.open(file_path.c_str());
	if (!input_file.is_open()) {
		return error(404, NOT_FOUND_DESCRIPTION);
	}
	string res_file_body = string(
		std::istreambuf_iterator<char>(input_file),
		std::istreambuf_iterator<char>()
	);
	input_file.close();
	Headers header;

	if (download){
		cout << file_path << endl;
		const string filename = file_path.substr(file_path.find_last_of('/') + 1);
		header[HEADER_DOWNLOAD] = "attachment; filename=\"" + filename + "\"";
	}
	
	header[HEADER_CONTENT_TYPE] = get_content_type(file_path);
	return get_response(200, header, res_file_body);
}