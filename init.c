/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaqbour <mmaqbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:55:51 by drtaili           #+#    #+#             */
/*   Updated: 2023/09/06 16:31:04 by mmaqbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	loading_texture1(t_data *data)
{
	data->cnv_img1 = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			"./xpmimg/eagle.xpm",
			&data->tex_w, &data->tex_h);
	if (data->cnv_img1 == NULL)
		return ;
	data->cnv_addr1 = (int *)mlx_get_data_addr(data->cnv_img1, &data->cnv_bpp1,
			&data->cnv_ll1, &data->cnv_en1);
	data->cnv_img2 = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			"./xpmimg/greystone.xpm",
			&data->tex_w, &data->tex_h);
	if (data->cnv_img2 == NULL)
		return ;
	data->cnv_addr2 = (int *)mlx_get_data_addr(data->cnv_img2, &data->cnv_bpp2,
			&data->cnv_ll2, &data->cnv_en2);
}

void	loading_texture2(t_data *data)
{
	data->cnv_img3 = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			"./xpmimg/mossy.xpm",
			&data->tex_w, &data->tex_h);
	if (data->cnv_img3 == NULL)
		return ;
	data->cnv_addr3 = (int *)mlx_get_data_addr(data->cnv_img3, &data->cnv_bpp3,
			&data->cnv_ll3, &data->cnv_en3);
	data->cnv_img4 = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			"./xpmimg/wood.xpm",
			&data->tex_w, &data->tex_h);
	if (data->cnv_img4 == NULL)
		return ;
	data->cnv_addr4 = (int *)mlx_get_data_addr(data->cnv_img4, &data->cnv_bpp4,
			&data->cnv_ll4, &data->cnv_en4);
}

void	ft_init(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	loading_texture1(data);
	loading_texture2(data);
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->addr = (int *)mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length,
			&data->endian);
	data->pos.x = MAP_WIDTH / 2;
	data->pos.y = MAP_HEIGHT / 2;
	data->dir.x = -1;
	data->dir.y = 0;
	data->rot = 180;
	data->keycode_move = -1;
	data->keycode_rotate = -1;
	data->keycode_sides = -1;
	data->mouse_move = 0;
	data->plane.x = 0;
	data->plane.y = 0.66;
	data->store_x = WIN_WIDTH / 2;
}
