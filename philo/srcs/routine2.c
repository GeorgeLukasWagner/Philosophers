/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:19:22 by gwagner           #+#    #+#             */
/*   Updated: 2024/11/11 11:58:10 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <bits/pthreadtypes.h>

void	ft_podox(t_philo *philo)
{
	dead_message(philo);
}

void	ft_put_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->is_taken = false;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->is_taken = false;
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	philo->action = THINK;
	if (philo->data->exit == 0)
		printf("%zu %d is thinking\n",
			get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	fork_loop(t_philo *philo)
{
	while (!take_forks(philo))
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->exit)
		{
			pthread_mutex_unlock(&philo->data->death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death);
		if (check_death(philo))
		{
			ft_podox(philo);
			break ;
		}
	}
}
