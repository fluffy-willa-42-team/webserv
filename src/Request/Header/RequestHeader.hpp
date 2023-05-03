/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:00 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 11:48:20 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHEADER_HPP
# define REQUESTHEADER_HPP

/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>

#include "using.hpp"

/* ************************************************************************** */

class RequestHeader {
	public:
		RequestHeader(const string& input);
		
		bool valid;
		
		string method;			//	GET
		string path;			//	/test
		string protocol;		//	HTTP/1.1
		string host;			//	www.example.com
		size_t port;			//	8080

		map<string, string> non_mandatory;
	
		class InvalidRequest : public std::exception { public: virtual const char* what() const throw() { return ("Invalid Request"); } };
	
	private:
		bool parse_line(const string& line, size_t index);
		bool parseStartLine(const string& line);
		bool parseHostHeader(const string& line);
		bool parseHeader(const string& line);
};

/* ************************************************************************** */

#endif /* REQUESTHEADER_HPP */