#include "response.hpp"

bool is_file_cgi(const Location& loc, const string& filename, string& cgi_bin){
	for (map<string, string>::const_iterator ite = loc.cgi_pass.begin(); ite != loc.cgi_pass.end(); ite++){
		if (endsWith(filename, ite->first)){
			cgi_bin = ite->second;
			return true;
		}
	}
	return false;
}

string cgi(const string& cgi_bin, const string& filepath){
	cout << "CGI: " << cgi_bin << " | " << filepath << endl;
	Headers headers;
	return get_response(200, headers, ":D");
}