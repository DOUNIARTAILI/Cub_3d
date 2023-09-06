/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaqbour <mmaqbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:40:04 by drtaili           #+#    #+#             */
/*   Updated: 2023/09/06 16:34:04 by mmaqbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	rot_right(t_data *data)
{
	double	olddirx;
	double	oldplanex;

	if (data->mouse_move)
	{
		data->mouse_move = 0;
		data->keycode_rotate = -1;
	}
	data->turn_direction = -1;
	data->rot = data->rot + data->turn_direction * (ROTSPEED * 180 / M_PI);
	olddirx = data->dir.x;
	data->dir.x = data->dir.x * cos(-ROTSPEED)
		- data->dir.y * sin(-ROTSPEED);
	data->dir.y = olddirx * sin(-ROTSPEED) + data->dir.y * cos(-ROTSPEED);
	oldplanex = data->plane.x;
	data->plane.x = data->plane.x * cos(-ROTSPEED)
		- data->plane.y * sin(-ROTSPEED);
	data->plane.y = oldplanex * sin(-ROTSPEED)
		+ data->plane.y * cos(-ROTSPEED);
}

void	rot_left_right(t_data *data, int keycode)
{
	double	olddirx;
	double	oldplanex;

	if (keycode == 124)
		rot_right(data);
	else if (keycode == 123)
	{
		if (data->mouse_move)
		{
			data->mouse_move = 0;
			data->keycode_rotate = -1;
		}
		data->turn_direction = 1;
		data->rot = data->rot + data->turn_direction * (ROTSPEED * 180 / M_PI);
		olddirx = data->dir.x;
		data->dir.x = data->dir.x * cos(ROTSPEED) - data->dir.y * sin(ROTSPEED);
		data->dir.y = olddirx * sin(ROTSPEED) + data->dir.y * cos(ROTSPEED);
		oldplanex = data->plane.x;
		data->plane.x = data->plane.x * cos(ROTSPEED)
			- data->plane.y * sin(ROTSPEED);
		data->plane.y = oldplanex * sin(ROTSPEED)
			+ data->plane.y * cos(ROTSPEED);
	}
}

void	move_shape(t_data *data)
{
	if (data->keycode_move == 13 || data->keycode_move == 1)
		move_back_and_forth(data, data->keycode_move);
	if (data->keycode_sides == 2 || data->keycode_sides == 0)
		move_sideways(data, data->keycode_sides);
	if (data->keycode_rotate == 123 || data->keycode_rotate == 124)
		rot_left_right(data, data->keycode_rotate);
}
