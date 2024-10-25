/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:45:59 by fsulvac           #+#    #+#             */
/*   Updated: 2024/07/23 17:46:01 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>    //printf
# include <stdlib.h>   //malloc free
# include <string.h>   //memset
# include <sys/time.h> //getimeoftheday
# include <unistd.h>   // write usleep
/* pthread_create,


	pthread_detach,
	pthread_join,
	pthread_mutex_init,
	pthread_mutex_destroy,
	pthread_mutex_lock,
	pthread_mutex_unlock */
# include <errno.h>   // EPERM EINVAL
# include <limits.h>  // INT_MAX
# include <stdbool.h> //for boolen

// *** ANSI colors ***
# define RESET "\033[0m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define RED "\033[31;1m"

// *** Simplify Code ****
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

// *** Line too long ***
# define ERROR_MSG "Please use philo with five or six arguments !"
# define ERROR_MSG_TWO "./philo nbr_philo time2die time2eat time2sleep max_eat"

// *** Opcode for handle pthreads ***

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}						t_opcode;

// *** STRUCTURE ***

typedef struct s_fork
{
	t_mtx				fork;
	long				id;
	bool				flag;
}						t_fork;

typedef struct s_philo
{
	long				id;
	t_fork				*first_fork;
	t_fork				*second_fork;
	long				last_meals;
	long				meals_counter;
	pthread_t			thread;
	bool				die;
	bool				full;
	t_table				*table;
	t_mtx				philo_mtx;
}						t_philo;

struct					s_table
{
	long				time2die;
	long				time2eat;
	long				time2sleep;
	long				max_eat;
	long				number_philo;
	long				start_simulation;
	long				threads_running_nbr;
	bool				end_simulation;
	bool				all_full;
	bool				all_threads_ready;
	pthread_t			monitor;
	t_philo				philo[200];
	t_fork				fork[200];
	t_mtx				write_mtx;
	t_mtx				table_mtx;
};

//*** Parse ***
bool					parse(int ac, char **av, t_table *table);

//*** Utils ***
void					print_error(char *s);
bool					simulation_finished(t_table *table);
void					wait_all_threads(t_table *table);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);

/// *** Data Init ***
void					data_init(t_table *table);

// *** Handle ***

void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void					safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);

// *** Acces Mutex ****
void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
long					get_long(t_mtx *mutex, long *value);
void					set_long(t_mtx *mutex, long *dst, long value);
void					increase_long(t_mtx *mutex, long *value);

// *** Time ***
long					get_elapsed_time_ms(long timestamp_start);
long					gettime(void);
void					precise_sleep(t_table *table, long ms);

// *** Action ***
void					print_message(t_table *table, char *str, long id);
void					eat(t_philo *philo);
void					dream(t_philo *philo, t_table *table);
void					think(t_philo *philo, t_table *table, bool pre_sim);
void					print_message_err(t_table *table, char *str, long id);

// *** Simulation ***
void					begin_simulation(t_table *table);

// *** Monitor ***
void					*monitor_simulation(void *pointer);

// *** Clean ***

void					clean(t_table *table);
#endif