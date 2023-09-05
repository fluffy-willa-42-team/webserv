#include "Error.hpp"

string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string(
		std::istreambuf_iterator<char>(input_file),
		std::istreambuf_iterator<char>()
	);
}

void replace_string(string& input, const string& pattern_in, const string& pattern_out){
    size_t pos = 0;

    while ((pos = input.find(pattern_in, pos)) != std::string::npos) {
        input.replace(pos, pattern_in.length(), pattern_out);
        pos += pattern_out.length();
    }
}

Error::Error()
: code(0), message(""), description("")
{}

Error::Error(u_int32_t code, string message, string description)
: code(code), message(message), description(description)
{}

Error::~Error(){}

const Error& Error::operator=(const Error& other){
	this->code = other.code;
	this->message = other.message;
	this->description = other.description;
	return *this;
}

const string Error::http(){
	string error_file = readFileIntoString("./errors/error.html");
	replace_string(error_file, "{{code}}", code);
	replace_string(error_file, "{{error_desc}}", message);
	if (message.length() > 0){
		replace_string(error_file, "{{error_message}}", message);
	}

	map<string, string> header;
	header["Content-Type"] = "text/html";
	header["Content-Length"] = "text/html";
	return ;
}
// 	"HTTP/1.1 200 OK
// Content-Type: text/html
// Content-Length: 112

// <html>
// <head>
// 	<title>200 OK</title>
// 	</head>
// 	<body>
// 			<h1>OK</h1>
// 			<p>The request was successful.</p>
// 	</body>
// </html>"