/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:27:20 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 09:47:00 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

std::ostream& operator<<(std::ostream& out, const Request& req){
	out << req.header.method << " " << req.header.path << " {" << endl;
	out << "    host: " << req.header.host << ":" << req.header.port << endl;
	out << "}";
	return out;
}