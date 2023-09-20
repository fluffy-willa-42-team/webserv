#include "http.hpp"

const Server& find_server(const Config& config, Headers req_headers){
	const string host = req_headers[HEADER_HOST];
	
	for (vector<Server>::const_iterator serv = config.servers.begin(); serv != config.servers.end(); serv++){
		cout << host << " | " << serv->host << endl;
		if (host == serv->host || host == serv->host + ":" + numberToString(serv->port)){
			return *serv;
		}
		if ((	serv->host == "localhost" && (host == "127.0.0.1" || host == string("127.0.0.1") + ":" + numberToString(serv->port)))
			|| (serv->host == "127.0.0.1" && (host == "localhost" || host == string("localhost") + ":" + numberToString(serv->port)))
		){
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

	cout << req_path << endl;

	for (vector<Location>::const_iterator loc = serv.locations.begin(); loc != serv.locations.end(); loc++){
		cout << "loc: " << loc->path << endl;
	}
	return serv.locations[0];
}