/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:14:16 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/07/27 13:30:42 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_x(void *param)
{
	t_vars	*vars;

	vars = (t_vars *) param;
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	key_hook(int keycode, void *param)
{
	t_vars	*vars;

	vars = (t_vars *) param;
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	do_none(void *data)
{
	(void) data;
	return (0);
}
