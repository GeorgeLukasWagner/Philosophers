/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:38:16 by gwagner           #+#    #+#             */
/*   Updated: 2024/11/11 12:34:43 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.philo_nb = ft_atoi(argv[1]);
	data.time_die = ft_atoi(argv[2]);
	data.time_eat = ft_atoi(argv[3]);
	data.time_sleep = ft_atoi(argv[4]);
	data.start_time = get_time();
	data.exit = false;
	pthread_mutex_init(&data.print, NULL);
	pthread_mutex_init(&data.death, NULL);
	if (argc == 6)
		data.eat_nb = ft_atoi(argv[5]);
	else
		data.eat_nb = -1;
	return (data);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if ((i + 1) % 2 == 0)
			data->forks[i].id = (i + 1) % data->philo_nb;
		else
			data->forks[i].id = -1;
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		data->forks[i].is_taken = false;
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].action = THINK;
		data->philos[i].is_dead = false;
		data->philos[i].time = get_time();
		data->philos[i].data = data;
		data->philos[i].eat_cnt = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_nb];
		i++;
	}
}

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_create(&data->philos[i].thread,
			NULL, routine, &data->philos[i]);
		ft_sleep(1, &data->philos[i]);
		i++;
	}
}
