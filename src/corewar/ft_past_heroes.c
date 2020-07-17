/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_past_heroes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include "corewar.h"

static int	ft_welcome_heroes(t_data *data)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!(data->vis_on))
		ft_printf(YELLOW"Introducing  contestants ..."RESET"\n");
	while (i < MAX_PLAYERS)
	{
		if (data->hero_list[i].id)
		{
			++count;
			ft_set_color(white + i + 1);
			if (!(data->vis_on))
				ft_printf(\
				"  * Player %d, weighting %d bytes, \"%s\" (\"%s\") !\n",
					data->hero_list[i].id, data->hero_list[i].header.prog_size,
					data->hero_list[i].header.prog_name,
					data->hero_list[i].header.comment);
		}
		++i;
	}
	if (!(data->vis_on))
		ft_printf(RESET"\n");
	return (count);
}

void		ft_past_heroes(t_game *game, t_data *data)
{
	int		count;
	int		i;
	int		step;
	size_t	temp;

	i = MAX_PLAYERS;
	count = ft_welcome_heroes(data);
	game->player_count = count;
	step = MEM_SIZE / count;
	while (i--)
	{
		if (data->hero_list[i].id)
		{
			--count;
			ft_memcpy(game->arena + count * step,
					data->hero_list[i].program,
					data->hero_list[i].header.prog_size);
			temp = data->hero_list[i].header.prog_size;
			while (temp--)
				game->color[count * step + temp] = white + i + 1;
		}
	}
	game->input = data;
}
