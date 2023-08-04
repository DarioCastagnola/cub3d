/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:42:02 by dcastagn          #+#    #+#             */
/*   Updated: 2023/08/04 14:45:29 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	is_colliding(t_game *game, double y, double x)
{
	if (game->parser.map[(int)y][(int)x] == '0')
		return (0);
	if (game->parser.map[(int)y][(int)x] == 'O')
		return (0);
	if (game->parser.map[(int)y][(int)x] == 'd')
		return (0);
	return (1);
}
