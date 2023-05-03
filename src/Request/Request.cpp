/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:27:20 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 09:37:39 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

std::ostream& operator<<(std::ostream& out, const Request& req){
	(void) req;
	out << "Test";
	return out;
}