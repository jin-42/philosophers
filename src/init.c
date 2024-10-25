/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:12 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:13 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, long positions)
{
	long	philo_nbr;

	philo_nbr = philo->table->number_philo;
	if (philo->id % 2 == 1)
	{
		philo->first_fork = &(forks[(positions + 1) % philo_nbr]);
		philo->second_fork = &(forks[positions]);
	}
	else
	{
		philo->first_fork = &(forks[positions]);
		philo->second_fork = &(forks[(positions + 1) % philo_nbr]);
	}
}

void	philo_init(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->number_philo)
	{
		safe_mutex_handle(&(table->philo[i].philo_mtx), INIT);
		table->philo[i].id = i + 1;
		table->philo[i].table = table;
		table->philo[i].meals_counter = 0;
		table->philo[i].last_meals = 0;
		table->philo[i].die = false;
		table->philo[i].full = false;
		assign_forks(&(table->philo[i]), table->fork, i);
	}
}

void	data_init(t_table *table)
{
	long	i;

	table->start_simulation = 0;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	safe_mutex_handle((&table->table_mtx), INIT);
	safe_mutex_handle(&(table->write_mtx), INIT);
	i = -1;
	table->all_full = false;
	while (++i < table->number_philo)
	{
		safe_mutex_handle((&table->fork[i].fork), INIT);
		table->fork[i].id = i;
		table->fork[i].flag = false;
	}
	philo_init(table);
}
