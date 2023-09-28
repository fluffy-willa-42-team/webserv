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

string parse_cgi_response(const string& cgi_response, Headers& headers, string& body){
	return body;
}