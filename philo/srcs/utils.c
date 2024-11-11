/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:36:05 by gwagner           #+#    #+#             */
/*   Updated: 2024/11/11 12:26:46 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <sched.h>
#include <stdbool.h>

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (false);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool	ft_sleep(size_t time, t_philo *philo)
{
	size_t	i;

	i = get_time();
	while (get_time() - i < time)
	{
		if (is_dead(philo))
			return (true);
		usleep(time);
	}
	return (false);
}

bool	check_death(t_philo *philo)
{
	if (get_time() - philo->last_meal >= philo->data->time_die)
		return (true);
	return (false);
}
