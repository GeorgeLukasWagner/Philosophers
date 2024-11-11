/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:57:10 by gwagner           #+#    #+#             */
/*   Updated: 2024/11/08 12:18:24 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	error_handling(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("%s %s %s", "Usage: ./philo number_of_philosophers",
			"time_to_die time_to_eat time_to_sleep",
			"[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (check_args(argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	return (0);
}

int	check_data(t_data data)
{
	if (data.philo_nb > 200)
	{
		printf("Error: Invalid number of philosophers\n");
		return (1);
	}
	if (data.time_die < 60 || data.time_eat < 60 || data.time_sleep < 60
		|| data.time_die > 10000 || data.time_eat > 10000
		|| data.time_sleep > 10000)
	{
		printf("Error: Invalid time\n");
		return (1);
	}
	return (0);
}
