/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:04:26 by lde-mich          #+#    #+#             */
/*   Updated: 2023/07/11 11:50:02 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_size(t_game *game, char *path)
{
	char	*l;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(write(1, "Error\nMap not found\n", 20));
	l = get_next_line(fd);
	game->x = ft_strlen(l) - 1;
	game->y = 0;
	while (l)
	{
		l = get_next_line(fd);
		game->y++;
	}
	close(fd);
}

char	**ft_readmap(t_game *game, char *path)
{
	char	**mat;
	char	*l;
	int		fd;
	int		j;

	mat = (char **)malloc((game->y + 1) * sizeof(char *));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(write(1, "Error\nMap not found\n", 20));
	l = get_next_line(fd);
	game->x = ft_strlen(l) - 1;
	j = 0;
	while (l)
	{
		if (l[ft_strlen(l) - 1] == '\n')
			l[ft_strlen(l) - 1] = 0;
		mat[j] = l;                                                                                                                                       
		l = get_next_line(fd);
		j++;
	}
	mat[game->y] = 0;
	close(fd);
	return (mat);
}

void	ft_inimap(t_game *game)
{
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (game->readmap[y] && count <= 6)
	{
		if (game->readmap[y] && game->readmap[y][0] != 0)
		{
			count++;
			y++;
		}
		else
			y++;
	}
	game->inimap = y - 1;
}

void	ft_map(t_game *game)
{
	int	y;
	int	j;

	ft_inimap(game);
	game->themap = (char **)malloc((game->y + 1) * sizeof(char *));
	y = game->inimap;
	printf("%d\n", game->inimap);
	j = 0;
	while (game->readmap[y])
	{
		game->themap[j] = ft_strdup(game->readmap[y]);
		j++;
		y++;
	}
	game->themap[j] = 0;
}