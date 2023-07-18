/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:59:32 by lde-mich          #+#    #+#             */
/*   Updated: 2023/07/17 11:41:38 by lde-mich         ###   ########.fr       */
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

void	ft_check_texture(t_parser *parser)
{
	int		x;
	int		y;
	int		count;
	char	*temp;

	y = 0;
	temp = NULL;
	count = 0;
	while (parser->readmap[y] && count < 4)
	{
		x = 0;
		while (parser->readmap[y][x] == 32)
			x++;
		temp = ft_substr(parser->readmap[y], x, 2);
		if (ft_strncmp(temp, "NO", 2) && ft_strncmp(temp, "SO", 2)
			&& ft_strncmp(temp, "WE", 2) && ft_strncmp(temp, "EA", 2))
			ft_free_err(parser, "Error\nTexture not supported\n");
		count++;
		free(temp);
		y++;
	}
}
