/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:12:23 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 09:13:28 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

/* ************************************************************************** */

#include <iostream>
#include <ResponseHeader.hpp>

/* ************************************************************************** */

class Response {
	private:
		ResponseHeader header;
	protected:

	public:
		Response();
		~Response();
		Response(const Response& other);
		const Response& operator=(const Response& other);

		virtual std::string toString() = 0;
		
};

/* ************************************************************************** */

#endif /* RESPONSE_HPP */