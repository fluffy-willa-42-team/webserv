#include <Get.hpp>

Get::Get(const Request& req) : Response(req){
	cout << PURPLE << "Constructing a GET method" << RESET << endl;
}

string Get::toString() const {
	stringstream res;
	res << "HTTP/1.1" << " " << "[Status code]" << " " << "[Status Message]" << endl
		<< "Date: " << "[Date]" << endl
		<< "Server: " << "[Server name]" << endl
		<< "Content-Length: " << "[Content Length]" << endl
		<< "Content-Type: [Content Type]" << endl
		<< endl
		<< content;
	return res.str();
}

/*

HTTP/1.1 200 OK
Date: Tue, 11 May 2023 12:00:00 GMT
Server: Apache/2.4.6 (CentOS) OpenSSL/1.0.2k-fips
Last-Modified: Mon, 10 May 2023 12:00:00 GMT
ETag: "123456-789-abc"
Content-Length: 1234
Content-Type: text/html; charset=UTF-8

<html>
<head>
	<title>Example Page</title>
</head>
<body>
	<h1>Hello World!</h1>
	<p>This is an example page.</p>
</body>
</html>

*/