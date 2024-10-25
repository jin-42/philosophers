/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:19 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:21 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 *  philo_count time2die time2eat time2sleep [meals_count]
 */
int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 6 || ac == 5)
	{
		if (parse(ac, av, &table) == false)
			return (1);
		data_init(&table);
		begin_simulation(&table);
		clean(&table);
	}
	else
		return (print_error(ERROR_MSG), print_error(ERROR_MSG_TWO), 1);
}
