/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:00 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 09:25:00 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHEADER_HPP
# define REQUESTHEADER_HPP

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

class RequestHeader {
	private:
		std::string method		= "";	//	GET
		std::string path		= "";	//	/test
		std::string protocol	= "";	//	HTTP/1.1
		std::string host		= "";	//	Host: www.example.com
		std::string userAgent	= "";	//	User-Agent: Mozilla/5.0
		std::string accept		= "";	//	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
		std::string connection	= "";	//	Connection: keep-alive
	protected:
	public:
		RequestHeader(){}
		~RequestHeader(){}
		RequestHeader(const RequestHeader& other){(void) other;}
		const RequestHeader& operator=(const RequestHeader& other){
			(void) other;
			return (*this);
		}
};

/* ************************************************************************** */

#endif /* REQUESTHEADER_HPP */