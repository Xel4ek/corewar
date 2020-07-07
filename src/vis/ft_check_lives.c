/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_lives.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

static void	ft_redraw_life(t_window *win, int player, int life)
{
	t_point begin;

	begin.x = CHAMP_X + 20 + CHAMP_NEXT * player + 35 * (life - 1);
	begin.y = CHAMP_Y + 100;
	begin.color = win->champs[player].color;
	ft_draw_heart(win, begin, begin.color);
}

static void	ft_delete_life(t_window *win, int player, int life)
{
	t_point begin;
	t_point end;

	begin.x = CHAMP_X + 15 + 230 * (player - 1) + 35 * (life - 1);
	begin.y = CHAMP_Y + 100;
	begin.color = C_BLACK;
	end.x = 30;
	end.y = 28;
	ft_fill_rectangle(win, begin, end);
}

static void	ft_redraw(t_window *win, int i, int lifes)
{
	/*if (lifes > win->champs[i].lifes)
		while (win->champs[i].lifes < lifes)
		{
			win->champs[i].lifes++;
			ft_redraw_life(win, i, win->champs[i].lifes);
		}
	else*/
	while (win->champs[i].lifes > lifes)
	{
		ft_delete_life(win, i + 1, win->champs[i].lifes);
		win->champs[i].lifes--;
	}
}

void		ft_check_lifes(t_window *win)
{
	//int sum;
	int i;
	int lifes;

	//i = -1;
	//sum = 0;
	//while (++i < 4)
	//    sum += win->game->lives_count[i];
	i = -1;
	while (++i < 4)
	{
		if (win->champs[i].id)
		{
			if (win->champs[i].life_count <= win->game->lives_count[i])
				win->champs[i].life_count = win->game->lives_count[i];
			else if (win->champs[i].lifes > 1)
			{
				lifes = win->champs[i].lifes - 1;
				ft_redraw(win, i, lifes);
				//win->champs[i].life_count = win->game->lives_count[i];
				//lifes = (int)((double)win->champs[i].lifes * ((double)win->game->lives_count[i] / (double)win->champs[i].life_count));
				//ft_redraw(win, i, lifes);
			}
			else if (win->champs[i].life_count && !win->game->lives_count[i])
				ft_redraw(win, i, 0);
		}
 /*       lifes = 0;
		if (win->champs[i].id && \
		win->game->lives_count[i] >= sum / win->champ_count)
			lifes = 5;
		else if (win->champs[i].id && \
		win->game->lives_count[i] && sum != 0)
			lifes = win->game->lives_count[i] / \
			(sum / (win->champ_count * 4));
		if (win->champs[i].id && lifes != win->champs[i].lifes)
			ft_redraw(win, i, lifes);*/
		win->game->lives_count[i] = 0;
	}
	win->game->doomsday = false;
}
