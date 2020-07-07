/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "vis.h"
#include <time.h>
#include <pthread.h>

static void	*ft_game(void *gameptr)
{
	t_game	*game;

	game = (t_game *)gameptr;
	game->input->quiet = true;
	if (ft_battle_vis(game))
		ft_print_arena(game);
	if (game->input->dump <= 0 ||
		game->input->dump >= game->total_cycles)
		ft_print_result(game);
	return (NULL);
}

void		ft_open_window(t_window **win, t_game *game)
{
	*win = ft_init_window();
	(*win)->game = game;
	ft_draw_grid(*win);
}

void		ft_loop(t_window *win)
{
	mlx_loop_hook(win->mlx, ft_redraw_game_field, (void *)win);
	mlx_key_hook(win->win, ft_key_press, (void *)win);
	mlx_hook(win->win, 17, 0, ft_close_window, (void *)win);
	mlx_loop(win->mlx);
}

int			main(int argc, char **argv)
{
	t_game		*game;
	t_err		err;
	t_data		*data;
	t_window	*win;
	pthread_t	game_thread;

	if (argc > 1)
	{
		if ((err = ft_parse_input(argc, argv, &data)))
			ft_print_error(err);
		if (!(game = ft_init_game()))
			return (0);
		if (err == success)
		{
			ft_past_heroes(game, data);
			if ((err = ft_init_cursors(game)))
				ft_print_error(err);
			ft_open_window(&win, game);
			if (pthread_create(&game_thread, NULL, ft_game, (void *)game))
				ft_print_error(err);
			ft_loop(win);
		}
	}
	else
		ft_usage();
	return (0);
}
