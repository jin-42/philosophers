/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:09 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:11 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (opcode == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		pthread_mutex_destroy(mutex);
	else
	{
		print_error("Wrong opcode for mutex handle");
	}
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	if (opcode == CREATE)
		pthread_create(thread, NULL, foo, data);
	else if (opcode == JOIN)
		pthread_join(*thread, NULL);
	else if (opcode == DETACH)
		pthread_detach(*thread);
	else
	{
		print_error("Wrong opcode for thread");
	}
}
