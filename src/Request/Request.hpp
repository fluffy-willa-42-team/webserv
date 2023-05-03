/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:05 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 11:31:49 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

/* ************************************************************************** */

#include <iostream>
#include <RequestHeader.hpp>

/* ************************************************************************** */

class Request {
	private:
		RequestHeader header;
		string data;
	public:
		Request(const std::string& input);

		bool isValid(){ return this->header.valid; }

		friend std::ostream& operator<<(std::ostream& out, const Request& req);
};

/* ************************************************************************** */

#endif /* REQUEST_HPP */