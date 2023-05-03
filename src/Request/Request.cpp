/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:27:20 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 10:07:20 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

std::ostream& operator<<(std::ostream& out, const Request& req){
	out << req.header.method << " " << req.header.path << " {" << endl;
	out << "    protocol: "		<< req.header.protocol	<< endl;
	out << "    host: "			<< req.header.host	<< ":" << req.header.port << endl;
	for (map<string, string>::const_iterator ite = req.header.non_mandatory.begin(); ite != req.header.non_mandatory.end(); ite++){
		out << "    " << ite->first << ": "	<< ite->second << endl;
	}
	out << "}";
	return out;
}