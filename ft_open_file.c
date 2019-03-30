/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:43:13 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/30 18:28:09 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

// ft_open_file_layout()
// {
// 	kiss_window_event(&window2, &e, &draw);
// 	kiss_window_event(&window->win, &window->e, &window->layout->draw);
// 	textbox1_event(&textbox1, &e, &vscrollbar1,
// 	&textbox2, &vscrollbar2, &label_sel, &window->layout->draw);
// 	vscrollbar1_event(&vscrollbar1, &e, &textbox1,
// 	&window->layout->draw);
// 	textbox2_event(&textbox2, &e, &vscrollbar2, &window->layout->entry,
// 	&window->layout->draw);
// 	vscrollbar2_event(&vscrollbar2, &e, &textbox2, &window->layout->draw);
// 	button_ok1_event(&button_ok1, &e, &win, &window2,
// 	&label_sel, &entry, &label_res,	&progressbar,
// 	&draw);
// 	button_cancel_event(&button_cancel, &e, &quit,
// 	&draw);
// 	kiss_entry_event(&entry, &e, &draw);
// 	button_ok2_event(&button_ok2, &e, &win, &window2,
// 	&progressbar, &draw);
// 	button_event_tomenu(&menu, &e, &draw, &onstart, &mode);
// 	if (window->layout->draw == 0)
// 	    return ;
// 	SDL_RenderClear(window->ren);
// 	kiss_window_draw(&window->win, window->ren);
// 	kiss_label_draw(&window->o_file->label1, window->ren);
// 	kiss_label_draw(&window->o_file->label2, window->ren);
// 	kiss_textbox_draw(&window->o_file->textbox1, window->ren);
// 	kiss_vscrollbar_draw(&window->o_file->vscrollbar1, window->ren);
// 	kiss_textbox_draw(&window->o_file->textbox2, window->ren);
// 	kiss_vscrollbar_draw(&window->o_file->vscrollbar2, window->ren);
// 	kiss_label_draw(&window->o_file->label_sel, window->ren);
// 	kiss_entry_draw(&window->o_file->entry, window->ren);
// 	kiss_button_draw(&window->o_file->menu, window->ren);
// 	kiss_button_draw(&window->o_file->button_ok1, window->ren);
// 	kiss_button_draw(&window->o_file->button_cancel, window->ren);
// 	kiss_window_draw(&window->o_file->window2, window->ren);
// 	kiss_label_draw(&window->o_file->label_res, window->ren);
// 	kiss_progressbar_draw(&window->o_file->progressbar, window->ren);
// 	kiss_button_draw(&window->o_file->button_ok2, window->ren);
// 	SDL_RenderPresent(window->o_file->ren);
// 	if (strlen(window->o_file->label_res.text) && window->layout->flag != 5)
// 	{
// 		SDL_Window *new_w;
// 		new_w = SDL_CreateWindow("win", 0, 0, 500, 500, 0);
// 		SDL_Surface *image;
// 		SDL_Surface *win_surface;
// 		win_surface = SDL_GetWindowSurface(new_w);
// 		image = SDL_LoadBMP(label_res.text);
// 		SDL_BlitSurface(image, NULL, win_surface, NULL);
// 		SDL_UpdateWindowSurface(new_w);
// 		printf("%s\n\n\n", label_res.text);
// 		window->layout->flag = 5;
// 		// window->layout->draw = 0;
// 	}    
// }