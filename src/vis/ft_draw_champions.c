/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_champions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "mlx.h"

static void	ft_draw_lifes(t_window *win, t_point begin, int color)
{
	int i;

	i = 0;
	while (++i < 6)
	{
		ft_draw_heart(win, begin, color);
		begin.x += 35;
	}
}

static void	ft_print_multiline(t_window *win, t_point begin, \
								int color, char *str)
{
	char	temp;
	char	*nex_line;
	int		len;

	len = ft_strlen(str);
	if (len > CHAMP_MAXLEN)
	{
		temp = str[CHAMP_MAXLEN];
		str[CHAMP_MAXLEN] = '\0';
		mlx_string_put(win->mlx, win->win, begin.x, begin.y, color, str);
		begin.x += 130;
		mlx_string_put(win->mlx, win->win, begin.x, begin.y, color, "...");
		str[CHAMP_MAXLEN] = temp;
	}
	else
		mlx_string_put(win->mlx, win->win, begin.x, begin.y, color, str);
}

void		ft_draw_champion(t_window *win, t_point begin, int color, int i)
{
	char	*name;

	name = win->game->input->hero_list[i].header.prog_name;
	begin.x += 20;
	begin.y += 20;
	ft_print_multiline(win, begin, color, name);
	begin.y += 35;
	name = win->game->input->hero_list[i].header.comment;
	ft_print_multiline(win, begin, color, name);
	begin.y += 45;
	win->champs[i].color = color;
	win->champs[i].lifes = 5;
	win->champs[i].life_count = 0;
	ft_draw_lifes(win, begin, color);
}
