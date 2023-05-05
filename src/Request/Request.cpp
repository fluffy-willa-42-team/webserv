/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:27:20 by awillems          #+#    #+#             */
/*   Updated: 2023/05/05 09:51:19 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "test.hpp"

Request::Request(const std::string& input) : valid(false), port(80), data("")
{
	try
	{
		std::stringstream test(input);
		string line;

		if (input.length() < 1)
			return ;

		size_t i = 0;
		while (std::getline(test, line) && line.length() > 0)
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
					this->data = input.substr(data_pos + 2);
			}
		}
		this->valid = true;
	}
	catch(const InvalidRequest& e){
		if (SHOW_ERROR_IN_PARSING)
			cout << e.what() << endl;
	}
}

std::ostream& operator<<(std::ostream& out, const Request& req){
	// if (!req.header.valid){
	// 	out << "Invalid Request";
	// 	return out;
	// }
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