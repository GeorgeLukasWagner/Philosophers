/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:16:55 by gwagner           #+#    #+#             */
/*   Updated: 2024/11/11 12:31:32 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <pthread.h>

bool	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->is_taken)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (false);
	}
	fork->is_taken = true;
	pthread_mutex_unlock(&fork->mutex);
	return (true);
}

bool	take_forks(t_philo *philo)
{
	if (!take_fork(philo->left_fork) || philo->id == philo->left_fork->id)
		return (false);
	if (!take_fork(philo->right_fork) || philo->id == philo->right_fork->id)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		philo->left_fork->is_taken = false;
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return (false);
	}
	philo->left_fork->id = philo->id;
	philo->right_fork->id = philo->id;
	return (true);
}

void	ft_eat(t_philo *philo)
{
	philo->last_meal = get_time();
	philo->action = EAT;
	if (philo->data->exit == 0)
	{
		eat_message(philo);
		philo->eat_cnt++;
		ft_sleep(philo->data->time_eat, philo);
	}
}

void	ft_nap(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->exit == 0)
	{
		pthread_mutex_unlock(&philo->data->print);
		sleep_message(philo);
		ft_sleep(philo->data->time_sleep, philo);
	}
	else
		pthread_mutex_unlock(&philo->data->print);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	while (!check_exit(philo) && philo->data->eat_nb != philo->eat_cnt)
	{
		ft_think(philo);
		if (check_exit(philo))
			break ;
		if (philo->data->philo_nb == 1)
		{
			ft_sleep(philo->data->time_die, philo);
			dead_message(philo);
			break ;
		}
		fork_loop(philo);
		if (check_exit(philo))
			break ;
		ft_eat(philo);
		ft_put_forks(philo);
		ft_nap(philo);
	}
	return (0);
}
