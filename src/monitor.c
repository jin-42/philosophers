/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:22 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:24 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	last_print(t_table *table, long id)
{
	long long	time;

	safe_mutex_handle(&table->write_mtx, LOCK);
	time = gettime() - table->start_simulation;
	printf(RED "%lld %ld died\n" RESET, time, id);
	safe_mutex_handle(&table->write_mtx, UNLOCK);
}

static bool	is_end_condition(t_table *table)
{
	t_philo	*philos;
	bool	is_dead;
	int		nb_full;
	int		i;

	i = -1;
	philos = table->philo;
	nb_full = 0;
	is_dead = false;
	while (++i < table->number_philo && is_dead == false)
	{
		set_bool(&(philos[i].philo_mtx), &is_dead,
			get_elapsed_time_ms(get_long(&(philos[i].philo_mtx),
					&philos[i].last_meals)) >= table->time2die);
		if (get_bool(&(philos[i].philo_mtx), &philos[i].full))
			nb_full++;
		if (is_dead == true || nb_full == table->number_philo)
		{
			set_bool(&table->table_mtx, &table->end_simulation, true);
			if (is_dead)
				last_print(table, philos[i].id);
		}
	}
	return (is_dead || (nb_full == table->number_philo));
}

void	*monitor_simulation(void *pointer)
{
	t_table	*table;

	table = (t_table *)pointer;
	while (!all_threads_running(&table->table_mtx, &table->threads_running_nbr,
			table->number_philo))
		;
	while (!is_end_condition(table))
	{
		usleep(300);
	}
	return (NULL);
}
