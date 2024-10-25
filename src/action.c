/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:45:59 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:01 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_message(t_table *table, char *str, long id)
{
	long	time;

	if (simulation_finished(table))
		return ;
	safe_mutex_handle(&table->write_mtx, LOCK);
	time = gettime() - table->start_simulation;
	if ((table))
		printf(GREEN "%ld %ld %s\n" RESET, time, id, str);
	safe_mutex_handle(&table->write_mtx, UNLOCK);
}

void	print_message_err(t_table *table, char *str, long id)
{
	long	time;

	if (simulation_finished(table))
		return ;
	safe_mutex_handle(&table->write_mtx, LOCK);
	time = gettime() - table->start_simulation;
	if ((table))
		printf(RED "%ld %ld %s\n" RESET, time, id, str);
	safe_mutex_handle(&table->write_mtx, UNLOCK);
}

void	eat(t_philo *philo)
{
	safe_mutex_handle(&(philo->first_fork->fork), LOCK);
	safe_mutex_handle(&(philo->second_fork->fork), LOCK);
	philo->first_fork->flag = true;
	philo->second_fork->flag = true;
	print_message(philo->table, "has taken a fork", philo->id);
	print_message(philo->table, "has taken a fork", philo->id);
	philo->meals_counter++;
	set_long(&philo->philo_mtx, &philo->last_meals, gettime());
	print_message(philo->table, "is eating", philo->id);
	precise_sleep(philo->table, philo->table->time2eat);
	if (philo->meals_counter == philo->table->max_eat)
		set_bool(&philo->philo_mtx, &philo->full, true);
	philo->first_fork->flag = false;
	philo->second_fork->flag = false;
	safe_mutex_handle(&(philo->first_fork->fork), UNLOCK);
	safe_mutex_handle(&(philo->second_fork->fork), UNLOCK);
}

void	dream(t_philo *philo, t_table *table)
{
	print_message(table, "is sleeping", philo->id);
	precise_sleep(table, table->time2sleep);
}

void	think(t_philo *philo, t_table *table, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (pre_sim == false)
		print_message(table, "is thinking", philo->id);
	if (table->number_philo % 2 == 0)
		return ;
	t_eat = table->time2eat;
	t_sleep = table->time2sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_sleep(table, t_think * 0.10);
}
