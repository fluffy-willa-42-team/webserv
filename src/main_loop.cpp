#include "Listener.hpp"

void start(map<int, Listener>& listeners, bool& loop, const Config& config){
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
		// for (map<int, Listener>::iterator ite = listeners.begin(); ite != listeners.end();){
			// e_status status = ite->second.try_exec(config);
			// if (status == S_STOP){
				// ite->second.stop();
				// std::map<int, Listener>::iterator temp = ite;
				// ite++;
				// listeners.erase(temp);
			// }
			// else {
				// ite++;
			// }
		// }
		break; //TODO remove
	}
}
