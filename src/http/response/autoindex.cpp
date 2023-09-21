#include "http.hpp"

static const string raw_autoindex_fragment_file		= readFileIntoString("./src/html/autoindex_fragment_file.html");
static const string raw_autoindex_fragment_folder	= readFileIntoString("./src/html/autoindex_fragment_folder.html");
static const string raw_autoindex					= readFileIntoString("./src/html/autoindex.html");

string get_response(u_int32_t code, map<string, string> headers, string body);

string get_autoindex_html(const string& path, const string& gobacklink, const vector<AutoindexInput>& values){
	string autoindex_file = raw_autoindex;

	replace_string(autoindex_file, "{{path}}", path);
	replace_string(autoindex_file, "{{gobacklink}}", gobacklink);

	stringstream fragment;
	for (vector<AutoindexInput>::const_iterator it = values.begin(); it != values.end(); it++){
		string autoindex_fragment_file;
		if (it->type == AINDEX_FOLDER){
			autoindex_fragment_file = raw_autoindex_fragment_folder;
			replace_string(autoindex_fragment_file, "{{link}}", it->path);
			replace_string(autoindex_fragment_file, "{{name}}", it->name);
			fragment << autoindex_fragment_file;
		}
	}
	for (vector<AutoindexInput>::const_iterator it = values.begin(); it != values.end(); it++){
		string autoindex_fragment_file;
		if (it->type == AINDEX_FILE){
			autoindex_fragment_file = raw_autoindex_fragment_file;
			replace_string(autoindex_fragment_file, "{{link}}", it->path);
			replace_string(autoindex_fragment_file, "{{name}}", it->name);
			fragment << autoindex_fragment_file;
		}
	}

	replace_string(autoindex_file, "{{fragment}}", fragment.str());
	return autoindex_file;
}

string test(){
	vector<AutoindexInput> test;
	for (int i = 0; i < 10; i++){
		AutoindexInput tmp;
		tmp.name = "/test" + numberToString(i);
		tmp.path = "/test" + numberToString(i);
		if (i % 2){
			tmp.type = AINDEX_FILE;
		}
		else {
			tmp.type = AINDEX_FOLDER;
		}
		test.push_back(tmp);
	}

	string res = get_autoindex_html("/php/test", "/test", test);

	map<string, string> header;
	header["Content-Type"] = "text/html";
	return get_response(200, header, res);
}
