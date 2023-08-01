/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:59:32 by lde-mich          #+#    #+#             */
/*   Updated: 2023/08/01 12:15:17 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_inidata(t_parser *parser)
{
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (parser->readmap[y] && count <= 4)
	{
		if (parser->readmap[y] && parser->readmap[y][0] != 0)
		{
			count++;
			y++;
		}
		else
			y++;
	}
	parser->inidata = y - 1;
}

void	ft_check_rgb(int y, t_parser *parser)
{
	char	**temp;
	char	**temp1;
	int		i;

	temp = ft_split(parser->readmap[y], 32);
	i = -1;
	while (temp[++i])
		temp1 = ft_split(temp[i], 44);
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
	ft_free_mat(temp);
	ft_free_mat(temp1);
}

void	ft_check_fc(t_parser *parser)
{
	int		x;
	int		y;
	int		count;

	ft_inidata(parser);
	y = parser->inidata;
	count = 0;
	while (parser->readmap[y] && count < 2)
	{
		x = 0;
		while (parser->readmap[y][x] == 32)
			x++;
		if (parser->readmap[y][x] == 70 || parser->readmap[y][x] == 67)
			ft_check_rgb(y, parser);
		else
			ft_free_err(parser, "Error\nRgb not supported\n");
		y++;
		count++;
	}
}

void	ft_check_texture(t_parser *parser, t_game *game)
{
	int		y;
	char	**temp;
	int		i;

	y = 0;
	i = -1;
	temp = NULL;
	while (parser->readmap[y] && y < 4)
	{
		temp = ft_split(parser->readmap[y], 32);
		ft_load_image(game, temp);
		ft_free_mat(temp);
		y++;
	}
	if (!game->walls[0].img || !game->walls[1].img || !game->walls[2].img
		|| !game->walls[3].img)
		ft_free_err(parser, "Error: image not found\n");
	while (++i < 4)
	game->walls[i].addr = mlx_get_data_addr(game->walls[i].img,
		&game->walls[i].bpp,&game->walls[i].ll,
		&game->walls[i].endian);

}
