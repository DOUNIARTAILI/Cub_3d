/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaqbour <mmaqbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:33:46 by mmaqbour          #+#    #+#             */
/*   Updated: 2023/09/06 10:03:35 by mmaqbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (x > WIN_WIDTH || y > WIN_HEIGHT || x <= 0 || y <= 0)
		return ;
    data->addr[y * WIN_WIDTH + x] = color;
}

void	draw_tile(int x, int y, int type, t_data *data)
{
	int	index_x;
	int	index_y;
	int	color;

	index_x = x - 1;
	index_y = y;
	while (index_y < (y + MINI_TILE_S))
	{
		if (++index_x < (x + MINI_TILE_S))
		{
			if (type == 1)
				color = BLACK;
			else if (type == 0)
				color = GRAY;
		    my_mlx_pixel_put(data, index_x, index_y, color);
        }
		else
		{
			index_x = x - 1;
			index_y++;
		}
	}
}

int	raycast_draw(double rot, double dist, int side, t_data *param)
{
	int		i;
	t_data	*data;

	data = param;
	int y_index = (data->pos.y * MINI_TILE_S);
	int x_index = (data->pos.x * MINI_TILE_S);
	i = 0;
	while (i++ < dist)
	{
		my_mlx_pixel_put(data, y_index, x_index, BLACK);
		x_index += side * cos(rot * M_PI / 180);
		y_index += side * -sin(rot * M_PI / 180);
	}
	return (1);
}

void	draw_fov(t_data *data)
{
	double	rotation_angle;
	double	begin_X;
	double	begin_Y;
    double		i;

	i = 0;
	rotation_angle = data->rot + 30;
	while (rotation_angle >= data->rot - 30)
	{	
		begin_X = data->pos.x * MINI_TILE_S;
		begin_Y = data->pos.y * MINI_TILE_S;
		i = 0;
    	while (i < 11)
    	{
        	begin_X += cos(rotation_angle * M_PI / 180);
        	begin_Y += sin(rotation_angle * M_PI / 180);
        	my_mlx_pixel_put(data, begin_Y, begin_X, 0xD1D0D0);
        	i++;
    	}
		rotation_angle = rotation_angle - 0.25;
	}
}
void	draw_player(t_data *data)
{
	double	rotation_angle;
	double	begin_X;
	double	begin_Y;
    int		i;

	i = 0;
	rotation_angle = data->rot + 30 + 180;
	while (rotation_angle >= data->rot - 30 + 180)
	{	
		begin_X = data->pos.x * MINI_TILE_S;
		begin_Y = data->pos.y * MINI_TILE_S;
		i = 0;
    	while (i < 5)
    	{
        	begin_X += cos(rotation_angle * M_PI / 180);
        	begin_Y += sin(rotation_angle * M_PI / 180);
        	my_mlx_pixel_put(data, begin_Y, begin_X, RED);
        	i++;
    	}
		rotation_angle = rotation_angle - 0.25;
	}
}

void	draw_map2d(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = 0;
	while (y < MAP_HEIGHT)
	{
		if (++x < MAP_WIDTH)
		{
			if (data->map[y][x] == 1)
				draw_tile(x * MINI_TILE_S, y * MINI_TILE_S, 1, data);
			else if (data->map[y][x] == 0)
				draw_tile(x * MINI_TILE_S, y * MINI_TILE_S, 0, data);
		}
		else
		{
			x = -1;
			y++;
		}
	}
	draw_player(data);
	draw_fov(data);
}
