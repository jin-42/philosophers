/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:24 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:26 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static bool	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (print_error("Please provide a positive value !"), NULL);
	if (!is_digit(*str))
		return (print_error("Please provide a digit"), NULL);
	number = str;
	while (is_digit(*str))
	{
		++str;
		++len;
	}
	if (len > 10)
		return (print_error("The value is too big. INT_MAX is the limit"),
			NULL);
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	if (!str)
	{
		return (-2);
	}
	while (is_digit(*str))
	{
		num = (num * 10) + (*str - '0');
		++str;
	}
	if (num > INT_MAX)
		return (print_error("The value is too big. INT_MAX is the limit"), -2);
	return (num);
}

/*
 *  philo_count time2die time2eat time2sleep [meals_count]
 */
bool	parse(int ac, char **av, t_table *table)
{
	table->number_philo = ft_atol(av[1]);
	if (table->number_philo > 200 || table->number_philo == 0)
		return (print_error("Number of philo superior 0 and inferior 200 !"),
			-2);
	table->time2die = ft_atol(av[2]);
	table->time2eat = ft_atol(av[3]);
	table->time2sleep = ft_atol(av[4]);
	if (ac == 6)
	{
		table->max_eat = ft_atol(av[5]);
		if (table->max_eat == 0)
			return (print_error("No dinner at the table ! We are hungry :("),
				false);
	}
	else
		table->max_eat = -1;
	if (table->number_philo == -2 || table->time2die == -2 || table->time2eat
		== -2 || table->time2sleep == -2 || table->max_eat == -2)
		return (false);
	return (true);
}
