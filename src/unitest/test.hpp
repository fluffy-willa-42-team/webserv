/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:05 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 12:12:18 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

/* ************************************************************************** */

typedef struct unitests {
    int			success_expected;
    const char* value;
}	unitests;

#define VERBOSE_TEST true
#define HIDE_SUCCESFULL_TEST true
#define SHOW_ERROR_IN_PARSING false

/* ************************************************************************** */

#endif /* TEST_HPP */