/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:12:37 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/30 20:09:15 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void	ft_events(t_env *env, t_window *window)
{
	while (SDL_PollEvent(&window->e))
	{
		if (window->e.type == SDL_QUIT)
		{
			window->layout->quit = 1;
		}
		kiss_window_event(&window->win, &window->e, &window->layout->draw);
		ft_event_mode_kind(window);
		ft_event_mode_kind2(window);
		ft_event_mode_kind3(env, window);
	}
}

void	ft_choose_layout(t_window *window)
{
	if (window->layout->onstart == 1)
		ft_start_layout(window);
	if (window->layout->client == 1)
		ft_client_layout(window);
	if (window->layout->server == 1)
		ft_server_layout(window);
	if (window->layout->cpu == 1 || window->layout->gpu == 1)
		ft_gpu_cpu_layout(window);
	if (window->layout->network == 1)
		ft_network_layout(window);
	if (window->layout->open == 1)
		ft_file_open_layout(window);
}

int     ui_create(t_env *env)
{
	t_window *window = malloc(sizeof(t_window));
	
	ft_init_ui(window);
	while (!window->layout->quit)
	{
		ft_events(env, window);
		ft_choose_layout(window);
	}
	kiss_clean(&window->objects);
	return (0);
}
