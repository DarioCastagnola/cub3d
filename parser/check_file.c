/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:59:32 by lde-mich          #+#    #+#             */
/*   Updated: 2023/09/06 14:46:54 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_rgb(int y, t_parser *parser)
{
	char	**temp;
	char	**temp1;
	int		i;

	temp = ft_split(parser->readmap[y], 32);
	if (!temp[1] || temp[2])
		ft_free_err(parser, "Error\nRgb missing\n");
	temp1 = ft_split(temp[1], 44);
	i = 0;
	while (temp1[i])
	{
		if (temp[0][0] == 70)
			parser->f[i] = ft_atoi(temp1[i]);
		else
			parser->c[i] = ft_atoi(temp1[i]);
		if (ft_atoi(temp1[i]) < 0 || ft_atoi(temp1[i]) > 255)
			ft_free_err(parser, "Error\nRgb not supported\n");
		i++;
	}
	if (i != 3)
		ft_free_err(parser, "Error\nRgb not supported\n");
	ft_free_mat(&temp);
	ft_free_mat(&temp1);
}

void	ft_check_fc(t_parser *parser)
{
	int		x;
	int		y;
	int		count;

	count = 0;
	y = 0;
	while (parser->readmap[y] && count < 2)
	{
		x = 0;
		while (parser->readmap[y][x] && count < 2)
		{
			if (parser->readmap[y][x] == 70 || parser->readmap[y][x] == 67)
			{
				ft_check_rgb(y, parser);
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 2)
		ft_free_err(parser, "Error\nRgb not supported\n");
}

void	ft_check_wall(t_parser *parser, t_game *game)
{
	int	i;

	ft_load_door_image(game);
	if (!game->walls[0].img || !game->walls[1].img || !game->walls[2].img
		|| !game->walls[3].img || !game->walls[4].img || !game->walls[5].img
		|| !game->walls[6].img || !game->walls[7].img || !game->walls[8].img
		|| !game->walls[9].img)
		ft_free_err(parser, "Error: image not found\n");
	i = -1;
	while (++i < 10)
		game->walls[i].addr = mlx_get_data_addr(game->walls[i].img,
				&game->walls[i].bpp, &game->walls[i].ll,
				&game->walls[i].endian);
}

void	ft_check_texture(t_parser *parser, t_game *game)
{
	int		y;
	char	**temp;
	int		i;

	i = -1;
	while (++i < 10)
		game->walls[i].img = 0;
	i = 0;
	y = 0;
	while (parser->readmap[y] && i < 4)
	{
		temp = ft_split(parser->readmap[y++], 32);
		if (temp[0] && temp[1])
			i += (!(!temp[2]) * 5) + ft_load_image(game, temp);
		ft_free_mat(&temp);
	}
	if (i != 4)
		ft_free_err(parser, "Error: image not found\n");
	ft_check_wall(parser, game);
}
