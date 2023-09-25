#include "http.hpp"

string clean_path(string req_path_param){
	if (req_path_param.find_first_of("?") != string::npos){
		req_path_param = req_path_param.substr(0, req_path_param.find_first_of("?"));
	}
	if (req_path_param.size() > 1 && req_path_param[req_path_param.size() - 1] == '/'){
		req_path_param = req_path_param.substr(0, req_path_param.size() - 1);
	}
	return req_path_param;
}

string clean_path_file(string req_path_param){
	if (req_path_param.find_first_of("?") != string::npos){
		req_path_param = req_path_param.substr(0, req_path_param.find_first_of("?"));
	}
	return req_path_param;
}

const Server& find_server(const Config& config, Headers req_headers){
	const string host = req_headers[HEADER_HOST];
	
	for (vector<Server>::const_iterator serv = config.servers.begin(); serv != config.servers.end(); serv++){
		if (host == serv->host || host == serv->host + ":" + numberToString(serv->port)){
			DEBUG_INFO_ << "Host Server Found: " << host << " | " << serv->host << endl;
			return *serv;
		}
	}
	throw exception();
}

const Location& find_location(const Server& serv, const string& req_path_param){
	string req_path = clean_path(req_path_param);

	for (vector<Location>::const_iterator loc = serv.locations.begin(); loc != serv.locations.end(); loc++){
		if (req_path == loc->path || startsWith(req_path, loc->path + "/")){
			DEBUG_INFO_ << "Server Location Found: " << req_path << " (" << loc->path << "}" << endl;
			return *loc;
		}
	}
	throw exception();
}