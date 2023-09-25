#include "response.hpp"

bool init_static_file(){
	if (readFileIntoString(AUTOINDEX_FILE, raw_autoindex) == S_ERROR){
		cerr << RED << "Failed to open: " << AUTOINDEX_FILE << RESET << endl;
		return false;
	}
	if (readFileIntoString(AUTOINDEX_FILE_FRAG_FILE, raw_autoindex_fragment_file) == S_ERROR){
		cerr << RED << "Failed to open: " << AUTOINDEX_FILE_FRAG_FILE << RESET << endl;
		return false;
	}
	if (readFileIntoString(AUTOINDEX_FILE_FRAG_FOLDER, raw_autoindex_fragment_folder) == S_ERROR){
		cerr << RED << "Failed to open: " << AUTOINDEX_FILE_FRAG_FOLDER << RESET << endl;
		return false;
	}
	if (readFileIntoString(ERROR_FILE, raw_error_file) == S_ERROR){
		cerr << RED << "Failed to open: " << ERROR_FILE << RESET << endl;
		return false;
	}
	return true;
}
