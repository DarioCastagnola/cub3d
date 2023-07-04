/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:39:41 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/04 11:42:09 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "gnl/gnl.h"
# include <fcntl.h>
# include <math.h>
# include <time.h>

// risoluzione
#define SCREEN_W 640
#define SCREEN_H 480

// Field Of View
#define FOV 0.66

// Pi
#define PI 3.14159

// passo di movimento e rotazione
#define MOVSPEED 0.1
#define ROTSPEED 0.05

// ---------- STRUCTS

typedef struct s_vectors
{
	double	x;
	double	y;
}	t_vectors;

typedef struct s_map
{
	char		**map;
	t_vectors	player_pos;
}	t_map;


typedef struct s_player
{
	t_vectors	pos;
	t_vectors	dir;
	t_vectors	mov_dir;
	t_vectors	plane;
	t_vectors	mov_speed;
	double		rot_speed;
	double		rot_dir;
}	t_player;

typedef struct s_ray
{
	t_vectors	draw_start;
	t_vectors	draw_end;
	t_vectors	side_dist;
	t_vectors	delta_dist;
	t_vectors	ray_dir;
	double		perp_wall_dist;
	double		camera_x;
	int			side;
	int			hit;
	int			line_height;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			color;
}	t_ray;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
	t_player		player;
    t_map           map;
	t_ray		ray;
}	t_game;

void	initialization(t_game *game);
int     player_initialization(t_game *game);
void	*null_error(char *message);

#endif