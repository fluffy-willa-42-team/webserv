#include "Config.hpp"

static e_status err(const string& message){
	cerr << RED << message << RESET << endl;
	return S_ERROR;
}

e_status Config::test_if_file_or_folder_exist(){
	for (vector<Server>::iterator serv = servers.begin(); serv != servers.end(); serv++){
		map<u_int32_t, string>& e_pages = serv->custom_error_page;
		for (map<u_int32_t, string>::iterator e_page = e_pages.begin(); e_page != e_pages.end(); e_page++){
			e_status res = readFileIntoString(e_page->second, e_page->second);
			if (res == S_ERROR){
				return err("Invalid custom error page: \"" + e_page->second + "\"");
			}
		}
		
		for (vector<Location>::const_iterator loc = serv->locations.begin(); loc != serv->locations.end(); loc++){
			if (loc->has_redirect){
				continue;
			}

			if (loc->root.empty() && loc->index.empty()){
				return err("You must have a Root option or a Index option per location");
			}
			if (!loc->root.empty() && !doesFolderExists(loc->root)){
				return err("Root folder inaccessible: \"" + loc->root + "\"");
			}
			
			if (!loc->cgi_pass.empty()){
				string cgi_pass = mergeFilePaths(loc->root, loc->cgi_pass);
				if (!isFileExecutable(cgi_pass)){
					return err("Invalid cgi executable: \"" + cgi_pass + "\"");
				}
			}

			if (!loc->index.empty()){
				string index = mergeFilePaths(loc->root, loc->index);
				if (!isFileReadable(index)){
					return err("Invalid index file: \"" + index + "\"");
				}
			}
		}
	}
	return S_CONTINUE;
}