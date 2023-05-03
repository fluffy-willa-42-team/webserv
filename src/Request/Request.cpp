/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:27:20 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 11:56:21 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(const std::string& input) :
	header(input), data("")
{
	size_t data_pos = input.find("\n\n");
	if (data_pos != string::npos)
		this->data = input.substr(data_pos + 2);
}

std::ostream& operator<<(std::ostream& out, const Request& req){
	// if (!req.header.valid){
	// 	out << "Invalid Request";
	// 	return out;
	// }
	out << req.header.method << " " << req.header.path << " {" << endl
	<< "    header: {" << endl
	<< "        protocol: "		<< req.header.protocol	<< endl
	<< "        host: "			<< req.header.host	<< ":" << req.header.port << endl;
	for (map<string, string>::const_iterator ite = req.header.non_mandatory.begin(); ite != req.header.non_mandatory.end(); ite++){
		out << "        " << ite->first << ": "	<< ite->second << endl;
	}
	out << "    }" << endl
	<< "    data: {"
	<< ((req.data.length() > 0) ? "\n" + req.data + "\n    " : "")
	<< "}" << endl
	<< "}";
	return out;
}