/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:04:26 by lde-mich          #+#    #+#             */
/*   Updated: 2023/08/07 15:00:12 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_size(t_parser *parser, char *path)
{
	char	*l;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(write(2, "Error\nMap not found\n", 20));
	l = get_next_line(fd);
	if (!l)
		ft_free_err(parser, "Error\nempty map\n");
	parser->x = ft_strlen(l) - 1;
	parser->y = 0;
	while (l)
	{
		free(l);
		l = get_next_line(fd);
		parser->y++;
	}
	free(l);
	close(fd);
}

char	**ft_readmap(t_parser *parser, char *path)
{
	char	**mat;
	char	*l;
	int		fd;
	int		j;

	mat = (char **)malloc((parser->y + 1) * sizeof(char *));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(write(1, "Error\nMap not found\n", 20));
	l = get_next_line(fd);
	if (!l)
		ft_free_err(parser, "Error\nempty map\n");
	parser->x = ft_strlen(l) - 1;
	j = 0;
	while (l)
	{
		if (l[ft_strlen(l) - 1] == '\n')
			l[ft_strlen(l) - 1] = 0;
		mat[j] = l;
		l = get_next_line(fd);
		j++;
	}
	mat[parser->y] = 0;
	close(fd);
	return (mat);
}

void	ft_inimap(t_parser *parser)
{
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (parser->readmap[y] && count <= 6)
	{
		if (parser->readmap[y] && parser->readmap[y][0] != 0)
		{
			count++;
			y++;
		}
		else
			y++;
	}
	parser->inimap = y - 1;
}

void	ft_map(t_parser *parser)
{
	int	y;
	int	j;

	ft_inimap(parser);
	parser->map = (char **)malloc((parser->y + 1) * sizeof(char *));
	y = parser->inimap;
	j = 0;
	while (parser->readmap[y])
	{
		parser->map[j] = ft_strdup(parser->readmap[y]);
		j++;
		y++;
	}
	parser->map[j] = 0;
}
