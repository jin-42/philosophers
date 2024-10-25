/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:31 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:32 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// *** All my time is in Milliseconde ***
long	get_elapsed_time_ms(long timestamp_start)
{
	return (gettime() - timestamp_start);
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(t_table *table, long ms)
{
	long	start_time;

	start_time = gettime();
	(void)table;
	while ((gettime() - start_time) < ms && (!(simulation_finished(table))))
		usleep(100);
}
