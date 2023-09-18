#include "Server.hpp"

void setup(map<int, Server>& servers){
	// Setup every server and delete all that fail setup
	for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end();){
		t_setup res = ite->second.setup();
		if (res.code != 0){
			cout << "Failed server setup code: " << res.code << " (" << res.message << ") " << res.err << endl;
			std::map<int, Server>::iterator temp = ite;
			ite++;
			servers.erase(temp);
		}
		else {
			ite++;
		}
	}
}

void start(map<int, Server>& servers, bool& loop){
	// Return if all failed to start
	if (servers.size() < 1){
		cout << "No Server Started" << endl;
		return ;
	}
	// Execute try_exec of all server at each execution.
	/*

	| 1 | 2 | 3 |            | 1 | 2 | 3 |            | 1 | 2 | 3 |
	|---|---|---|     =>     |---|---|---|     =>     |---|---|---|
	| x |   |   |            |   | x |   |            |   |   | x |
      ^															|
	  |															|
      O---------------------------------------------------------O
	
	*/
	while (loop){
		for (map<int, Server>::iterator ite = servers.begin(); ite != servers.end();){
			e_status status = ite->second.try_exec();
			if (status == S_STOP){
				ite->second.stop();
				std::map<int, Server>::iterator temp = ite;
				ite++;
				servers.erase(temp);
			}
			else {
				ite++;
			}
		}
	}
}
