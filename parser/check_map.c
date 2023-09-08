/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:45:56 by lde-mich          #+#    #+#             */
/*   Updated: 2023/09/08 11:55:18 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_player(t_parser *parser)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (parser->map[y])
	{
		x = 0;
		while (parser->map[y][x])
		{
			if (ft_strchr("NWSE", parser->map[y][x]))
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		ft_free_err(parser, "Error\nMap error\n");
}

void	ft_check_map(t_parser *parser)
{
	int	x;
	int	y;

	y = 0;
	while (parser->map[y])
	{
		x = 0;
		while (parser->map[y][x])
		{
			if (ft_strchr("0DNWSE", parser->map[y][x]))
			{
				if (parser->map[y - 1][x] == 32 || parser->map[y + 1][x] == 32
					|| parser->map[y][x - 1] == 32
					|| parser->map[y][x + 1] == 32)
					ft_free_err(parser, "Error\nnot surrounded by wall\n");
				else if (!parser->map[y - 1][x] || !parser->map[y + 1][x]
					|| !parser->map[y][x + 1] || !parser->map[y][x - 1])
					ft_free_err(parser, "Error\nnot surrounded by wall\n");
			}
			x++;
		}
		y++;
	}
}

void	ft_check_lmap(t_parser *parser)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (parser->map[y][x])
	{
		if (parser->map[y][x] == '0')
			ft_free_err(parser, "Error\nnot surrounded by wall\n");
		x++;
	}
	y = parser->mheight - 1;
	x = 0;
	while (parser->map[y][x])
	{
		if (parser->map[y][x] == '0')
			ft_free_err(parser, "Error\nnot surrounded by wall\n");
		x++;
	}
}

void	ft_check_symbol_map(t_parser *parser)
{
	int	y;
	int	x;

	y = 0;
	while (parser->map[y])
	{
		x = 0;
		while (parser->map[y][x])
		{
			if (!(parser->map[y][x] == 49 || parser->map[y][x] == 48
				|| parser->map[y][x] == 78 || parser->map[y][x] == 83
				|| parser->map[y][x] == 69 || parser->map[y][x] == 87
				|| parser->map[y][x] == 32 || parser->map[y][x] == 'D'))
				ft_free_err_img(parser, "Error\nSymbol not supported\n");
			x++;
		}
		y++;
	}
}
