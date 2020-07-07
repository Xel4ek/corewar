/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "mlx.h"
#include <stdlib.h>

static void	ft_full_champs_info(t_window *win)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		win->champs[i].id = 0;
		win->champs[i].color = ft_check_color(blue + i);
		win->champs[i].lifes = 5;
		win->champs[i].life_count = 0;
	}
}

t_window	*ft_init_window(void)
{
	t_window	*new;

	if (!(new = (t_window *)malloc(sizeof(t_window))))
		return (NULL);
	new->height = WINDOW_HEIGHT;
	new->width = WINDOW_WIDTH;
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, new->width, new->height, WINDOW_TITLE);
	ft_bzero(new->champs, sizeof(t_champ) * MAX_PLAYERS);
	new->colors = ft_memalloc(MEM_SIZE * sizeof(t_color));
	new->game = NULL;
	new->champ_count = 0;
	new->end = false;
	return (new);
}