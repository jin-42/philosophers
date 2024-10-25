/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:26 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:28 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meals, gettime());
	print_message(philo->table, "has taken a fork", philo->id);
	precise_sleep(philo->table, philo->table->time2die);
	print_message_err(philo->table, "died", philo->id);
	return (arg);
}

static void	pre_desynchronize(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_sleep(philo->table, philo->table->time2eat);
}

static void	*simulation(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	wait_all_threads(table);
	increase_long(&table->table_mtx, &table->threads_running_nbr);
	set_long(&philo->philo_mtx, &philo->last_meals, table->start_simulation);
	pre_desynchronize(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		dream(philo, table);
		think(philo, table, false);
	}
	return (data);
}

void	begin_simulation(t_table *table)
{
	int	i;

	i = -1;
	if (table->number_philo == 1)
	{
		safe_thread_handle(&(table->philo[0].thread), lone_philo,
			&table->philo[0], CREATE);
		table->start_simulation = gettime();
		set_bool(&table->table_mtx, &table->all_threads_ready, true);
		safe_thread_handle(&table->philo[0].thread, NULL, NULL, JOIN);
	}
	else
	{
		while (++i < table->number_philo)
			safe_thread_handle(&table->philo[i].thread, simulation,
				&table->philo[i], CREATE);
		safe_thread_handle(&table->monitor, monitor_simulation, table, CREATE);
		usleep(200000);
		table->start_simulation = gettime();
		set_bool(&table->table_mtx, &table->all_threads_ready, true);
		while (++i < table->number_philo)
			safe_thread_handle(&table->philo[i].thread, NULL, NULL, JOIN);
		safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
	}
}
