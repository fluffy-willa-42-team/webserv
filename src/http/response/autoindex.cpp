#include "response.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

static const string raw_autoindex_fragment_file		= readFileIntoString("./src/html/autoindex_fragment_file.html");
static const string raw_autoindex_fragment_folder	= readFileIntoString("./src/html/autoindex_fragment_folder.html");
static const string raw_autoindex					= readFileIntoString("./src/html/autoindex.html");

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

string get_autoindex(const string& req_path, const string& file_path){
	DIR* dir = opendir(file_path.c_str());
	if (!dir){
		if 		(errno == EACCES)	{ return error(403, "folder fail"); }
		else if (errno == ENOENT)	{ return error(404, "folder fail"); }
		else 						{ return error(500, "folder fail"); }
	}

	vector<AutoindexInput> autoindex_inputs;
	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL) {
		AutoindexInput newInput;
		struct stat file_info;
	
		string newPath = file_path + (file_path[file_path.size() -1] != '/' ? "/" : "") + entry->d_name;
		if (stat(newPath.c_str(), &file_info) == -1) {
			DEBUG_ << newPath << " could not be opened" << endl;
			continue ;
		}
		newInput.fileSize = file_info.st_size;
		newInput.name = entry->d_name;
		if (newInput.name == "." || newInput.name == ".."){
			continue ;
		}
		newInput.path = req_path + "/" + newInput.name;

		if (entry->d_type == DT_REG)		{ newInput.type = AINDEX_FILE; }
		else if (entry->d_type == DT_DIR)	{ newInput.type = AINDEX_FOLDER; }
		else if (entry->d_type == DT_LNK)	{}
		
		autoindex_inputs.push_back(newInput);
	}

	string res = get_autoindex_html(req_path, "/", autoindex_inputs);

	map<string, string> header;
	header["Content-Type"] = "text/html";
	return get_response(200, header, res);
}
