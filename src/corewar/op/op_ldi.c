/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_err	op_ldi(t_game *game)
{
	union u_types	type;
	t_cursor		*cursor;
	int				args[3];
	size_t			address;

	cursor = game->cursor;
	cursor->current = ft_mod(cursor->pc + OP_LEN, MEM_SIZE);
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	args[0] = ft_get_arg(game, type.args.arg1, true);
	args[1] = ft_get_arg(game, type.args.arg2, true);
	args[2] = ft_get_data(game, type.args.arg3);
	address = cursor->pc + (args[1] + args[0]) % IDX_MOD;
	cursor->regs[args[2] - 1] = ft_atoi_vm(game->arena, &address, REG_SIZE).v_4;
	cursor->carry = cursor->regs[args[2] - 1] ? false : true;
	return (success);
}
