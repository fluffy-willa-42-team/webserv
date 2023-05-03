/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:05 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 10:33:17 by awillems         ###   ########.fr       */
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

/* ************************************************************************** */

#endif /* TEST_HPP */