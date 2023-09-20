#include "http.hpp"

const Server& find_Server(const Config& config, Headers headers){
	return config.servers[0];
	// for (vector<Server>::const_iterator serv = config.servers.begin(); serv != config.servers.end(); serv++){
	// 	if (req_headers[HEADER_HOST] != serv->host){
	// 		continue;
	// 	}
	// 	cout << serv->host << endl;
	// }
}