/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:06:29 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/04 16:16:33 by dcastagn         ###   ########.fr       */
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

int raycasting(t_game *game)
{
  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame
  int x;

  while(!done())
  {
    x = 0;
    while(x < SCREEN_W)
    {
      //calculate ray position and direction
      //which box of the map we're iN

      //length of ray from current position to next x or y-side
      //length of ray from one x or y-side to next x or y-side
      //these are derived as:
      //deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
      //deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
      //which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
      //where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
      //unlike (dirX, dirY) is not 1, however this does not matter, only the
      //ratio between deltaDistX and deltaDistY matters, due to the way the DDA
      //stepping further below works. So the values can be computed as below.
      // Division through zero is prevented, even though technically that's not
      // needed in C++ with IEEE 754 floating point values.

      double perpWallDist;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(game->ray.ray_dir.x < 0)
      {
        game->ray.step_x = -1;
        game->ray.side_dist.x = (game->player.pos.x - game->ray.map_x) * game->ray.delta_dist.x;
      }
      else
      {
        game->ray.step_x = 1;
        game->ray.side_dist.x = (game->ray.map_x + 1.0 - game->player.pos.x) * game->ray.delta_dist.x;
      }
      if(game->ray.ray_dir.y < 0)
      {
        game->ray.step_y = -1;
        game->ray.side_dist.y = (game->player.pos.y - game->ray.map_y) * game->ray.delta_dist.y;
      }
      else
      {
        game->ray.step_y = 1;
        game->ray.side_dist.y = (game->ray.map_y + 1.0 - game->player.pos.y) * game->ray.delta_dist.y;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(game->ray.side_dist.x < game->ray.side_dist.y)
        {
          game->ray.side_dist.x += game->ray.delta_dist.x;
          game->ray.map_x += game->ray.step_x;
          side = 0;
        }
        else
        {
          game->ray.side_dist.y += game->ray.delta_dist.y;
          game->ray.map_y += game->ray.step_y;
          side = 1;
        }
        //Check if ray has hit a wall
        if (game->map.map[game->ray.map_x][game->ray.map_y] > 0)
          hit = 1;
      }
      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
      
      if (side == 0)
        game->ray.perp_wall_dist = (game->ray.side_dist.x - game->ray.delta_dist.x);
      else
        game->ray.perp_wall_dist = (game->ray.side_dist.y - game->ray.delta_dist.y);

      //Calculate height of line to draw on screen
      game->ray.line_height = (int)(SCREEN_H / game->ray.perp_wall_dist);

      //calculate lowest and highest pixel to fill in current stripe
      game->ray.draw_start = -game->ray.line_height / 2 + SCREEN_H / 2;
      if(game->ray.draw_start < 0) 
        game->ray.draw_start = 0;
      game->ray.draw_end = game->ray.line_height / 2 + SCREEN_H / 2;
      if(game->ray.draw_end >= SCREEN_H)
        game->ray.draw_end = SCREEN_H - 1;

      //choose wall color
      ColorRGB color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = RGB_Red;    break; //red
        case 2:  color = RGB_Green;  break; //green
        case 3:  color = RGB_Blue;   break; //blue
        case 4:  color = RGB_White;  break; //white
        default: color = RGB_Yellow; break; //yellow
      }

      //give x and y sides different brightness
      if(side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      verLine(x, drawStart, drawEnd, color);
      x++;
    }
    //timing for input and FPS counter
    oldTime = time;
    time = getTicks();
    double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    print(1.0 / frameTime); //FPS counter
    redraw();
    cls();

    //speed modifiers
    double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    readKeys();
    //move forward if no wall in front of you
    if(keyDown(SDLK_UP))
    {
      if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if(keyDown(SDLK_DOWN))
    {
      if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }
    //rotate to the right
    if(keyDown(SDLK_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if(keyDown(SDLK_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
  }
}