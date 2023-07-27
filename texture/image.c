/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:16:10 by lde-mich          #+#    #+#             */
/*   Updated: 2023/07/25 16:10:56 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_load_image(t_game *game, char **temp)
{
	if (!ft_strncmp(temp[0], "NO", 3))
		game->no_wall.img = mlx_xpm_file_to_image(game->mlx,
				temp[1], &game->no_wall.width, &game->no_wall.height);
	else if (!ft_strncmp(temp[0], "SO", 3))
		game->so_wall.img = mlx_xpm_file_to_image(game->mlx,
				temp[1], &game->so_wall.width, &game->so_wall.height);
	else if (!ft_strncmp(temp[0], "EA", 3))
		game->ea_wall.img = mlx_xpm_file_to_image(game->mlx,
				temp[1], &game->ea_wall.width, &game->ea_wall.height);
	else if (!ft_strncmp(temp[0], "WE", 3))
		game->we_wall.img = mlx_xpm_file_to_image(game->mlx,
				temp[1], &game->we_wall.width, &game->we_wall.height);
}