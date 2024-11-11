/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:50:23 by gwagner           #+#    #+#             */
/*   Updated: 2024/11/11 12:31:40 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <pthread.h>

bool	check_exit(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->exit)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (false);
}

void	dead_message(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (!check_exit(philo))
		printf("%zu %d died\n",
			get_time() - philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->data->death);
	philo->data->exit = true;
	pthread_mutex_unlock(&philo->data->death);
	philo->is_dead = true;
	pthread_mutex_unlock(&philo->data->print);
}

void	eat_message(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->exit == 0)
		printf("%zu %d is eating\n",
			get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	sleep_message(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	philo->action = SLEEP;
	if (philo->data->exit == 0)
		printf("%zu %d is sleeping\n",
			get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}
