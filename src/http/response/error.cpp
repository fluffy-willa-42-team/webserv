#include "response.hpp"

void replace_string(string& input, const string& pattern_in, const string& pattern_out);

string raw_error_file;
map<u_int32_t, string> error_codes_map;

string error(u_int32_t code, const string& message){
	string error_file(raw_error_file);
	stringstream code_str; code_str << code;
	replace_string(error_file, "{{code}}", code_str.str());
	replace_string(error_file, "{{error_desc}}", error_codes_map[code]);
	if (message.length() > 0){
		replace_string(error_file, "{{error_message}}", message);
	}
	else {
		replace_string(error_file, "{{error_message}}", "");
	}
	Headers header;
	header["Content-Type"] = "text/html";

	cout << RED << "=>" << raw_error_file << RESET << endl;
	return get_response(code, header, error_file);
}

string error_serv(const Server& serv, u_int32_t code, const string& message){
	map<u_int32_t, string>::const_iterator look = serv.custom_error_page.find(code);
	if (look != serv.custom_error_page.end()){
		return look->second;
	}
	// if (serv.custom_error_page[code])
	return error(code, message);
}

map<u_int32_t, string>& get_codes_map(){
	return error_codes_map;
}

bool is_valid_error_code(u_int32_t code){
	return map_has_key(error_codes_map, code);
}
