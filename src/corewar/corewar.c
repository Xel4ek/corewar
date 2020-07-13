#include "ft_printf.h"
#include "mlx.h"
#include "vis.h"
#include <time.h>
#include <pthread.h>

/*int main(int argc, char **argv)
{
	t_game *game;
	t_err err;
	t_data *data;

	ft_printf(CLR);
	if (argc > 1)
	{
		if ((err = ft_parse_input(argc, argv, &data)))
			ft_print_error(err);
		if (!(game = ft_init_game(NULL)))
			return (0); //memory allocated error
		if (err == success)
		{
			ft_past_heroes(game, data);
			if ((err = ft_init_cursors(game)))
				ft_print_error(err);
			if (ft_battle(game))
				ft_print_arena(game);
			if (game->input->dump <= 0 ||
			game->input->dump >= game->total_cycles)
				ft_print_result(game);
			ft_game_over(&game);
		}
	}
	else
		ft_usage();
	return 0;
}*/

static void	*ft_game(void *gameptr)
{
	t_game	*game;

	game = (t_game *)gameptr;
	pthread_mutex_lock(game->mutex);
	while(*(game->start) != true)
	{
		pthread_cond_wait(game->cv, game->mutex);
	}
	pthread_mutex_unlock(game->mutex);
	if (ft_battle(game))
		ft_print_arena(game);
	if (game->input->dump <= 0 ||
		game->input->dump >= game->total_cycles)
		ft_print_result(game);
	return (NULL);
}


static void		*ft_loop(void *winptr)
{
	t_window	*win;

	win = (t_window *)winptr;
	mlx_loop_hook(win->mlx, ft_redraw_game_field, (void *)win);
	mlx_key_hook(win->win, ft_key_press, (void *)win);
	mlx_mouse_hook(win->win, ft_mouse_hook, (void *)win);
	mlx_hook(win->win, 17, 0, ft_close_window, (void *)win);
	mlx_loop(win->mlx);
	return (NULL);
}

t_broker		*ft_init_broker(t_data *data)
{
	t_broker	*broker;
	t_game		*game;
	t_window	*win;

	broker = (t_broker *)malloc(sizeof(t_broker));
	broker->vis_on = data->vis_on;
	broker->game_start = false;
	broker->error = success;
	broker->fps = 0;
	pthread_mutex_init(&(broker->mutex), NULL);
	pthread_cond_init(&(broker->game_cv), NULL);
	if (!(game = ft_init_game(broker)))
	{
		broker->error = no_memory;
		return (broker);
	}
	ft_past_heroes(game, data);
	if ((broker->error = ft_init_cursors(game)))
		return (broker);
	pthread_create(&(broker->game), NULL, ft_game, (void *)game);
	if (broker->vis_on && (win = ft_init_window(game)))
	{
		broker->fps = DEFAULT_DELAY;
		game->input->quiet = true;
		ft_loop((void *) win);
	}
	else if (broker->vis_on)
	{
		broker->error = no_memory;
		return (broker);
	}
	else
	{
		pthread_mutex_lock(&(broker->mutex));
		broker->game_start = true;
		pthread_cond_signal(&(broker->game_cv));
		pthread_mutex_unlock(&(broker->mutex));
	}
	return (broker);
}


int			main(int argc, char **argv)
{
	t_err		err;
	t_data		*data;
	t_broker	*broker;

	if (argc > 1)
	{
		if ((err = ft_parse_input(argc, argv, &data)))
			ft_print_error(err);
		if (err == success)
		{
			broker = ft_init_broker(data);
			if (broker->error)
				ft_print_error(broker->error);
			if (!data->vis_on)
				pthread_join(broker->game, NULL);
		}
	}
	else
		ft_usage();
	return (0);
}
