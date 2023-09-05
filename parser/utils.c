/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:15:02 by lde-mich          #+#    #+#             */
/*   Updated: 2023/09/05 15:46:44 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_print_mat(char **mat)
{
	int	y;
	int	x;

	y = 0;
	while (mat[y])
	{
		x = 0;
		while (mat[y][x])
		{
			write(1, &mat[y][x], 1);
			x++;
		}
		y++;
		write(1, "\n", 1);
	}
}

void	ft_free_mat(char ***mat)
{
	int	i;

	i = -1;
	if (!(*mat))
		return ;
	while ((*mat)[++i])
		free((*mat)[i]);
	free(*mat);
	*mat = NULL;
}

void	ft_free_err_img(t_parser *parser, char *s)
{
	int	i;

	i = -1;
	while (++i < 10)
		if (parser->game->walls[i].img)
			mlx_destroy_image(parser->game->mlx, parser->game->walls[i].img);
	ft_free_mat(&parser->readmap);
	ft_free_mat(&parser->map);
	while (*s)
		write(2, s++, 1);
	exit(1);
}

void	ft_free_err(t_parser *parser, char *s)
{
	ft_free_mat(&parser->readmap);
	ft_free_mat(&parser->map);
	while (*s)
		write(2, s++, 1);
	exit(1);
}

void	ft_size_map(t_parser *parser)
{
	int	x;
	int	y;
	int	hx;

	hx = 0;
	y = 0;
	while (parser->map[y])
	{
		x = 0;
		while (parser->map[y][x])
		{
			x++;
			if (hx < x)
				hx = x;
		}
		y++;
	}
	parser->mheight = y;
	parser->mwidth = hx;
}
