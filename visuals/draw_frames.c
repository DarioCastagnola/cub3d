/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:42:48 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/06 16:42:34 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	draw_frames(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	raycaster(game);
    usleep(8000);
	return (0);
}