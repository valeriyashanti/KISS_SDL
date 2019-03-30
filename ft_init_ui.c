/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_ui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:54:22 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/23 19:24:42 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

int	ft_init_ui(t_window *window)
{
	window->ren = kiss_init(" -- RT -- ", &window->objects, 600, 1000);
	window->layout = malloc(sizeof(t_layout));
	if (!window->ren)
		return (-1);
	window->layout->draw = 1;
	window->layout->gpu = 0;
	window->layout->server = 0;
	window->layout->mode = 0;
	window->layout->open = 0;
	window->layout->cpu = 0;
	window->layout->onstart = 1;
	window->layout->quit = 0;
	window->layout->client = 0;
	window->layout->newwindow = 0;
	window->layout->network = 0;
	window->ip = "e2r4p6";
	window->label.textcolor.b = 255;
	return (0);
}
