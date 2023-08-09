/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:31:11 by dcastagn          #+#    #+#             */
/*   Updated: 2023/08/07 14:08:12 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	door_animation(t_game *game)
{
	if (game->frames < (DOOR_FRAMES * 4))
		game->ray.color = 4;
	else if (game->frames < (DOOR_FRAMES * 8))
		game->ray.color = 5;
	else if (game->frames < (DOOR_FRAMES * 12))
		game->ray.color = 6;
	else if (game->frames < (DOOR_FRAMES * 16))
		game->ray.color = 7;
	else if (game->frames < (DOOR_FRAMES * 20))
		game->ray.color = 8;
	else if (game->frames < (DOOR_FRAMES * 24))
		game->ray.color = 9;
	else
	{
		game->ray.color = 1;
		game->frames = 0;
	}
}

u_int64_t	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (u_int64_t)(1000)) + (time.tv_usec / 1000));
}

void	ft_sleep(u_int64_t time)
{
	u_int64_t	start;

	start = 0;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}
