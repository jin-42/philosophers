/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:36 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:37 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_error(char *s)
{
	printf("%s%s\n%s", RED, s, RESET);
}

bool	simulation_finished(t_table *table)
{
	if (get_bool(&(table->table_mtx), &table->end_simulation) == true)
		return (true);
	return (false);
}

// *** SPINLOCK ***
void	wait_all_threads(t_table *table)
{
	while (!(get_bool(&table->table_mtx, &table->all_threads_ready)))
		;
}

// *** Monitor wait until all threads are not running ***
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}
