/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:02 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:07 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// ** Terminate and cleaup ***/
void	clean(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_philo)
		safe_mutex_handle(&table->philo[i].philo_mtx, DESTROY);
	safe_mutex_handle(&table->write_mtx, DESTROY);
	safe_mutex_handle(&table->table_mtx, DESTROY);
	i = -1;
	while (++i < table->number_philo)
		safe_mutex_handle(&table->fork[i].fork, DESTROY);
}
