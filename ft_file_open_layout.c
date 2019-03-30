/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_open_layout.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:03:12 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/30 19:37:14 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void    ft_file_open_layout(t_window *window)
{
    int textbox_width =  300;

	window->layout->mode = 6;
	kiss_array_new(&window->objects);
	kiss_window_new(&window->win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
	strcpy(window->message, "THIS IS CLIENT MODE\n     CHOOSE FILE PATH:");
	kiss_label_new(&window->label, &window->win, window->message, window->win.rect.w / 2 - strlen(window->message) * kiss_textfont.advance / 2, 100);
	kiss_button_new(&window->btn.b_menu, &window->win, "TO MENU", 200, 800);
	kiss_button_new(&window->btn.upload, &window->win, "UPLOAD", 200, 290);
	kiss_entry_new(&window->btn.input, &window->win, 1, window->ip, 100, 240, 300);
	window->win.visible = 1;
	window->layout->client = 0;
	if (window->layout->draw == 0)
		return ;
	SDL_RenderClear(window->ren);
	kiss_window_draw(&window->win, window->ren);
	kiss_label_draw(&window->label, window->ren);
	kiss_button_draw(&window->btn.b_menu, window->ren);
	kiss_entry_draw(&window->btn.input, window->ren);
	kiss_button_draw(&window->btn.upload, window->ren);
	SDL_RenderPresent(window->ren);
	window->layout->draw = 0;
}