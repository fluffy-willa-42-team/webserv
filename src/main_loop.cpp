#include "Listener.hpp"

void setup(map<int, Listener>& listeners){
	// Setup every server and delete all that fail setup
	for (map<int, Listener>::iterator ite = listeners.begin(); ite != listeners.end();){
		t_setup res = ite->second.setup();
		if (res.code != 0){
			cout << "Failed server setup code: " << res.code << " (" << res.message << ") " << res.err << endl;
			std::map<int, Listener>::iterator temp = ite;
			ite++;
			listeners.erase(temp);
		}
		else {
			ite++;
		}
	}
}

void start(map<int, Listener>& listeners, bool& loop){
	// Return if all failed to start
	if (listeners.size() < 1){
		cout << "No Listener Started" << endl;
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
		for (map<int, Listener>::iterator ite = listeners.begin(); ite != listeners.end();){
			e_status status = ite->second.try_exec();
			if (status == S_STOP){
				ite->second.stop();
				std::map<int, Listener>::iterator temp = ite;
				ite++;
				listeners.erase(temp);
			}
			else {
				ite++;
			}
		}
	}
}
