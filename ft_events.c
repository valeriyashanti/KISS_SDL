/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:42:01 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/30 20:06:59 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void    ft_event_mode_kind(t_window *window)
{
	if (window->layout->mode == 2)
	{
		button_event_connect(&window->btn.get_ip, &window->e, &window->layout->draw, window->btn.input.text);
		button_event_tomenu(&window->btn.b_menu, &window->e, &window->layout->draw, &window->layout->onstart, &window->layout->mode);
		button_event_disconnect(&window->btn.disconect, &window->e, &window->layout->draw);
 		kiss_entry_event(&window->btn.input, &window->e, &window->layout->draw);
		if (window->layout->draw == 0)
			return ;
		SDL_RenderClear(window->ren);
		kiss_window_draw(&window->win, window->ren);
		kiss_label_draw(&window->label, window->ren);
		kiss_button_draw(&window->btn.get_ip, window->ren);
		kiss_button_draw(&window->btn.disconect, window->ren);
		kiss_entry_draw(&window->btn.input, window->ren);
		kiss_button_draw(&window->btn.b_menu, window->ren);
		SDL_RenderPresent(window->ren);
	}
	if (window->layout->mode == 0)
	{
		button_event_client(&window->btn.b_client, &window->e, &window->layout->draw, &window->layout->client, &window->layout->onstart);
		button_event_server(&window->btn.b_server, &window->e, &window->layout->draw, &window->layout->server, &window->layout->onstart);
	}
}

void    ft_event_mode_kind2(t_window *window)
{
	if (window->layout->mode == 1)
	{
		button_event_render(&window->btn.b_render, &window->e, &window->layout->draw);
		button_event_tomenu(&window->btn.b_menu, &window->e, &window->layout->draw, &window->layout->onstart, &window->layout->mode);
		button_event_cpu(&window->btn.b_cpu, &window->e, &window->layout->draw, &window->layout->cpu);
		button_event_gpu(&window->btn.b_gpu, &window->e, &window->layout->draw, &window->layout->gpu);
		button_event_network(&window->btn.b_network, &window->e, &window->layout->draw, &window->layout->network);
	}
			
	if (window->layout->mode == 4)
	{
		button_event_tomenu(&window->btn.b_menu, &window->e, &window->layout->draw, &window->layout->onstart, &window->layout->mode);
		button_event_open_f(&window->btn.open_file,  &window->e, &window->layout->draw, &window->layout->mode, &window->layout->open);
		button_event_server(&window->btn.b_server, &window->e, &window->layout->draw, &window->layout->server, &window->layout->onstart);
	}
	if (window->layout->mode == 5)
	{
		button_event_open_f(&window->btn.open_file,  &window->e, &window->layout->draw, &window->layout->mode, &window->layout->open);
		button_event_tomenu(&window->btn.b_menu, &window->e, &window->layout->draw, &window->layout->onstart, &window->layout->mode);
		button_event_server(&window->btn.b_server, &window->e, &window->layout->draw, &window->layout->server, &window->layout->onstart);
	}
}

void	ft_event_mode_kind3(t_env *env, t_window *window)
{
	if (window->layout->mode == 6)
	{
		env->addr = button_event_upload(&window->btn.upload, &window->e, &window->layout->draw, window->btn.input.text);
		button_event_tomenu(&window->btn.b_menu, &window->e, &window->layout->draw, &window->layout->onstart, &window->layout->mode);
 		kiss_entry_event(&window->btn.input, &window->e, &window->layout->draw);
		if (window->layout->draw == 0)
			return ;
		SDL_RenderClear(window->ren);
		kiss_window_draw(&window->win, window->ren);
		kiss_label_draw(&window->label, window->ren);
		kiss_button_draw(&window->btn.upload, window->ren);
		kiss_entry_draw(&window->btn.input, window->ren);
		kiss_button_draw(&window->btn.b_menu, window->ren);
		SDL_RenderPresent(window->ren);
	}
}
