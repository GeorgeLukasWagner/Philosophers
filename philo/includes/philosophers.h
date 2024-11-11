/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:36:04 by gwagner           #+#    #+#             */
/*   Updated: 2024/11/11 12:29:53 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sched.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <bits/pthreadtypes.h>

typedef struct s_data	t_data;

typedef enum e_act
{
	EAT,
	SLEEP,
	THINK
}	t_act;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
	bool			is_taken;
}	t_fork;

typedef struct s_philo
{
	int				id;
	size_t			time;
	size_t			last_meal;
	int				eat_cnt;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	t_act			action;
	t_data			*data;
	bool			is_dead;
}	t_philo;

typedef struct s_data
{
	int				philo_nb;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				eat_nb;
	size_t			start_time;
	bool			exit;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	t_fork			forks[200];
	t_philo			philos[200];
}	t_data;

int		error_handling(int argc, char **argv);
int		ft_atoi(char *str);
int		check_data(t_data data);
t_data	init_data(int argc, char **argv);
void	init_forks(t_data *data);
void	init_philos(t_data *data);
void	*routine(void *val);
bool	take_forks(t_philo *philo);
void	init_threads(t_data *data);
size_t	get_time(void);
bool	ft_sleep(size_t time, t_philo *philo);
bool	is_dead(t_philo *philo);
void	sleep_message(t_philo *philo);
void	eat_message(t_philo *philo);
void	dead_message(t_philo *philo);
bool	check_death(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_put_forks(t_philo *philo);
void	ft_podox(t_philo *philo);
void	fork_loop(t_philo *philo);
bool	check_exit(t_philo *philo);

#endif