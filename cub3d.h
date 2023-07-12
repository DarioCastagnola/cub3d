/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:39:41 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/12 14:27:44 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "gnl/gnl.h"
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>

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

# define RGB_RED 0x00FF0000
# define RGB_GREEN 0x0000FF00
# define RGB_BLUE 0x000000FF
# define RGB_YELLOW 0x00FFFF00
# define RGB_WHITE 0x00FFFFFF
# define RGB_DARK_GREY 0x00282828

// ---------- STRUCTS

typedef struct s_vectors
{
	double	x;
	double	y;
}	t_vectors;

typedef struct s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

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
	char			**themap;
	int				y;
	int				x;
	void			*mlx;
	void			*mlx_win;
	char			**readmap;
	int				inimap;
	double			frame_time;
	int				fps;
	u_int64_t		time;
	u_int64_t		old_time;
	t_player		player;
	t_ray			ray;
	t_data			data;
}	t_game;

void	ft_sleep(u_int64_t time);
int	start_game(t_game *game);
void	init_game(t_game *game);
u_int64_t	get_time(void);
int     player_initialization(t_game *game);
void	update_inputs(t_game *game);
void	*null_error(char *message);
int		key_hook_press(int key, t_game *game);
int		key_hook_release(int key, t_game *game);
void	raycaster(t_game *game);
int		draw_frames(t_game *game);
void	draw_line_on(t_data *img, t_vectors begin, t_vectors end, int color);

//Map related functions

void	ft_print_mat(char **mat);
void	ft_map(t_game *game);
char	**ft_readmap(t_game *game, char *path);
void	ft_check_size(t_game *game, char *path);

#endif