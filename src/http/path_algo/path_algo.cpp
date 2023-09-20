#include "http.hpp"

const Server& find_server(const Config& config, Headers req_headers){
	string host = req_headers[HEADER_HOST];
	
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