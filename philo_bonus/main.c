/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:29:15 by a1                #+#    #+#             */
/*   Updated: 2022/02/25 18:43:03 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;

	philo = NULL;
	if (init_argv(&data, argc, argv))
		return (0);
	printf("hello\n");
	return (0);
}
