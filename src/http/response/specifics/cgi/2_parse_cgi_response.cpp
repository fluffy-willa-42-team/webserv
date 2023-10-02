#include "response.hpp"

/*

X-Powered-By: PHP/8.0.30
Content-type: text/html; charset=UTF-8

<html>
	<head>
		<title>PHP index</title>
	</head>
	<body>
		<h1>PHP index</h1>
	</body>
</html>

<style>
	body {
		background-color: goldenrod;
	}

	h1 {
		color: black;
		text-align: center;
		padding: 5em;
	}
</style>

*/

e_status parse_cgi_response(const string& cgi_response, uint32_t& code, Headers& headers, string& body){
	size_t header_body_separator = cgi_response.find("\r\n\r\n");

    if (header_body_separator == string::npos) {
		return S_ERROR;
	}
	string header_string = cgi_response.substr(0, header_body_separator);
	body = cgi_response.substr(header_body_separator + 4);

	stringstream header_stream(header_string);
	string line;
	while (getline(header_stream, line) && removeCarriageReturn(line)) {
		size_t separator = line.find(": ");
		if (separator == string::npos) {
			continue;
		}
		string field_name = line.substr(0, separator);
		string field_value = line.substr(separator + 2);
		if (field_name == CGI_HEADER_STATUS){
			code = stringToNumber(string(field_value, 0, 3));
			if (code == 0){
				return S_ERROR;
			}
		}
		else {
			headers[field_name] = field_value;
		}
	}
    return S_CONTINUE;
}