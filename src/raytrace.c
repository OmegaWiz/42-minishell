/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:47:21 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/07/05 21:06:31 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	raytrace(t_vec2 p, t_vars *vars)
{
	t_ray	hit_ray;
	t_obj	*hit_obj;

	// printf("raytracing at pixel %.0f %.0f\n", p.x, p.y);
	hit_obj = raycast(p, vars, &hit_ray);
	if (hit_obj == NULL) // hit no object
		return (0); //for initial tests, there is no color ambience, return black
	if (is_shadow(hit_ray, vars) == true)
		return (0);
	return (get_color(hit_obj));
}

t_obj	*raycast(t_vec2 p, t_vars *vars, t_ray *hit_ray)
{
	t_ray	ray1;
	t_ray	ray2;
	t_list	*lst;
	t_obj	*hit_obj;
	float	min_dist;

	ray1 = get_ray(p, vars);
	min_dist = INFINITY;
	hit_obj = NULL;
	lst = vars->obj_list;
	while (lst)
	{
		if (is_intersect((t_obj *) (lst->content), &ray1, &ray2) == true)
		{
			if (distance(vars->camera.origin, ray2.origin) < min_dist)
			{
				min_dist = distance(vars->camera.origin, ray2.origin);
				hit_obj = (t_obj *) (lst->content);
				*hit_ray = ray2;
			}
		}
		lst = lst->next;
	}
	return (hit_obj);
}

bool	is_intersect(t_obj *obj, t_ray *ray1, t_ray *ray2)
{
	if (obj->type == SPHERE)
		return (intersect_sphere(obj, ray1, ray2));
	else if (obj->type == PLANE)
		return (intersect_plane(obj, ray1, ray2));
	return (false);
}

t_ray	get_ray(t_vec2 p, t_vars *vars)
{
	t_ray	ray;

	// printf("getting ray at pixel %.0f %.0f\n", p.x, p.y);
	ray.origin = vars->camera.origin;
	// printf("ray origin: %f %f %f\n", ray.origin.x, ray.origin.y, ray.origin.z);
	float half_fov = (vars->camera.fov / 2.0f) * M_PI / 180.0f;
	float x_angle = ((p.x / (float) WIN_WIDTH) * half_fov * 2) - half_fov;
	float y_angle = ((p.y / (float) WIN_HEIGHT) * half_fov * 2) - half_fov;
	float x_deviation = tanf(x_angle);
	float y_deviation = -tanf(y_angle);
	// printf("%f %f %f %f %f\n", half_fov, x_angle, y_angle, x_deviation, y_deviation);
	ray.direction.x = x_deviation * vars->cam_plane.width / 2.0f;
	ray.direction.y = y_deviation * vars->cam_plane.height / 2.0f;
	ray.direction.z = 1.0f;
	// printf("ray direction: %f %f %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
	return (ray);
}

float	distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)
			+ pow(p1.z - p2.z, 2)));
}
