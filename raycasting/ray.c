/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:06:29 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/07 16:19:16 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    initialization_raycasting(t_game *game, int x)
{
    game->ray.camera_x = 2.0 * (double)x / (double)SCREEN_W - 1;
	game->ray.ray_dir.x = game->player.dir.x
		+ game->player.plane.x * game->ray.camera_x;
	game->ray.ray_dir.y = game->player.dir.y
		+ game->player.plane.y * game->ray.camera_x;
	game->ray.map_x = (int)game->player.pos.x;
	game->ray.map_y = (int)game->player.pos.y;
	game->ray.delta_dist.x = 1e30;
	game->ray.delta_dist.y = 1e30;
	if (game->ray.ray_dir.x)
		game->ray.delta_dist.x = fabs(1 / game->ray.ray_dir.x);
	if (game->ray.ray_dir.y)
		game->ray.delta_dist.y = fabs(1 / game->ray.ray_dir.y);
	game->ray.hit = 0;
	game->ray.draw_start.x = x;
	game->ray.draw_end.x = x;
}

void	calculate_side_dist_and_step(t_game *game)
{
	if (game->ray.ray_dir.x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist.x = (game->player.pos.x - game->ray.map_x)
			* game->ray.delta_dist.x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist.x = (game->ray.map_x + 1.0 - game->player.pos.x)
			* game->ray.delta_dist.x;
	}
	if (game->ray.ray_dir.y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist.y = (game->player.pos.y - game->ray.map_y)
			* game->ray.delta_dist.y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist.y = (game->ray.map_y + 1.0 - game->player.pos.y)
			* game->ray.delta_dist.y;
	}
}

void  perform_dda(t_game *game)
{
	while(game->ray.hit == 0)
  	{
    	if(game->ray.side_dist.x < game->ray.side_dist.y)
    	{
      	game->ray.side_dist.x += game->ray.delta_dist.x;
      	game->ray.map_x += game->ray.step_x;
      	game->ray.side = 0;
    	}
    	else
    	{
    	game->ray.side_dist.y += game->ray.delta_dist.y;
		//printf("%f\n", game->ray.delta_dist.y);
    	game->ray.map_y += game->ray.step_y;
    	game->ray.side = 1;
    	}
        //Check if ray has hit a wall
		if (game->themap[game->ray.map_y][game->ray.map_x] != 0)
			game->ray.hit = 1;
    }
}

void  wall_view(t_game  *game)
{
      if (game->ray.side == 0)
        game->ray.perp_wall_dist = (game->ray.side_dist.x - game->ray.delta_dist.x);
      else
        game->ray.perp_wall_dist = (game->ray.side_dist.y - game->ray.delta_dist.y);
      game->ray.line_height = (int)(SCREEN_H / game->ray.perp_wall_dist);
      game->ray.draw_start.y = -game->ray.line_height / 2 + SCREEN_H / 2;
      if(game->ray.draw_start.y < 0) 
        game->ray.draw_start.y = 0;
      game->ray.draw_end.y = game->ray.line_height / 2 + SCREEN_H / 2;
      if(game->ray.draw_end.y >= SCREEN_H)
        game->ray.draw_end.y = SCREEN_H - 1;
}

void	select_texture(t_game *game)
{
	if (game->ray.side == 1 && game->player.pos.y <= game->ray.map_y)
		game->ray.color = 1;
	else if (game->ray.side == 1)
		game->ray.color = 0;
	else if (game->ray.side == 0 && game->player.pos.x <= game->ray.map_x)
		game->ray.color = 2;
	else if (game->ray.side == 0)
		game->ray.color = 3;
	else
		game->ray.color = 0;
}

void	draw_texture(t_game *game, int x)
{
	int	colors[4];
  (void)x;
  (void)colors;

	select_texture(game);
		colors[0] = RGB_BLUE;
		colors[1] = RGB_GREEN;
		colors[2] = RGB_RED;
		colors[3] = RGB_YELLOW;
		game->ray.color %= 4;
}

void	raycaster(t_game *game)
{
	int		x;

	x = -1;
	while (++x < SCREEN_H)
	{
		initialization_raycasting(game, x);
		calculate_side_dist_and_step(game);
		perform_dda(game);
		wall_view(game);
		draw_texture(game, x);
		draw_line_on(game->data.img, game->ray.draw_start, game->ray.delta_dist, game->ray.color);
	}
}
