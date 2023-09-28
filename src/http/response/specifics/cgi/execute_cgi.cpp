#include "response.hpp"

string exec_cgi(const Env& env, const string& cgi_bin){
	char **env_cast = createCopy(env);

	// execve()

	// char** ptr = env_cast;

    // while (*ptr) {
    //     cout << string(*ptr) << endl;
    //     ptr++;
    // }

	freeCopy(env, env_cast);


	return "OK";
}