#include "http.hpp"

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
	string req_path = req_path_param;

	// Removing params
	if (req_path.find_first_of("?") != string::npos){
		req_path = req_path.substr(0, req_path.find_first_of("?"));
	}

	for (vector<Location>::const_iterator loc = serv.locations.begin(); loc != serv.locations.end(); loc++){
		if (req_path == loc->path || startsWith(req_path, loc->path + "/")){
			DEBUG_INFO_ << "Server Location Found: " << req_path << " (" << loc->path << "}" << endl;
			return *loc;
		}
	}
	throw exception();
}