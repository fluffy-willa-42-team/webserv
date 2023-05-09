#include "Request.hpp"
#include "test.hpp"

Request::Request(const std::string& input) : valid(false), error_message(""), port(80), data("")
{
	try
	{
		stringstream test(input);
		string line;

		if (input.length() < 1)
			return ;

		size_t i = 0;
		while (std::getline(test, line) && line.length() > 0 && line != "\r")
		{
			parse_line(line, i);
			line.clear();
			i++;
		}
		if (i < 2){
			throw InvalidRequest("Missing Content");
		}
		if (line.length() == 0){
			if (std::getline(test, line)){
				size_t data_pos = input.find("\n\n");
				if (data_pos != string::npos)
					data = input.substr(data_pos + 2);
			}
		}
		valid = true;
	}
	catch(const InvalidRequest& e){
		error_message = e.what();
		if (SHOW_ERROR_IN_PARSING)
			cout << e.what() << endl;
	}
}

std::ostream& operator<<(std::ostream& out, const Request& req){
	if (!req.valid){
		out << "Invalid Request";
		return out;
	}
	out << req.method << " " << req.path << " {" << endl
	<< "    header: {" << endl
	<< "        protocol: "		<< req.protocol	<< endl
	<< "        host: "			<< req.host	<< ":" << req.port << endl;
	for (map<string, string>::const_iterator ite = req.headers.begin(); ite != req.headers.end(); ite++){
		out << "        " << ite->first << ": "	<< ite->second << endl;
	}
	out << "    }" << endl
	<< "    data: {"
	<< ((req.data.length() > 0) ? "\n" + req.data + "\n    " : "")
	<< "}" << endl
	<< "}";
	return out;
}