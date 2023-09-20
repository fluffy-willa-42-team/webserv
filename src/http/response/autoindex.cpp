#include "webserv.hpp"
#include "utils.hpp"

static const string raw_autoindex_fragment_file		= readFileIntoString("./src/html/autoindex_fragment_file.html");
static const string raw_autoindex_fragment_folder	= readFileIntoString("./src/html/autoindex_fragment_folder.html");
static const string raw_autoindex					= readFileIntoString("./src/html/autoindex.html");


