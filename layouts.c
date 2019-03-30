/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layouts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:35:58 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/30 19:39:30 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void	ft_start_layout(t_window *window)
{
	kiss_array_new(&window->objects);
	kiss_window_new(&window->win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
	strcpy(window->message, "СHOOSE YOUR MODE");
	kiss_label_new(&window->label, &window->win, window->message, window->win.rect.w / 2 - strlen(window->message) * kiss_textfont.advance / 2, 100);
	kiss_button_new(&window->btn.b_client, &window->win, "CLIENT", 200, 750);
	kiss_button_new(&window->btn.b_server, &window->win, "SERVER", 200, 800);
	window->layout->onstart = 0;
	window->win.visible = 1;
	if (window->layout->draw == 0)
		return ;
	SDL_RenderClear(window->ren);
	kiss_window_draw(&window->win, window->ren);
	kiss_button_draw(&window->btn.b_client,  window->ren);
	kiss_button_draw(&window->btn.b_server, window->ren);	
	kiss_label_draw(&window->label, window->ren);
	SDL_RenderPresent(window->ren);
}

void    ft_server_layout(t_window *window)
{
	window->layout->mode = 1;
	kiss_array_new(&window->objects);
	kiss_window_new(&window->win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
	strcpy(window->message, "THIS IS SERVER MODE");
	kiss_label_new(&window->label, &window->win, window->message, window->win.rect.w / 2 - strlen(window->message) * kiss_textfont.advance / 2, 100);
	kiss_button_new(&window->btn.b_cpu, &window->win, "CPU MODE", 200, 500);
	kiss_button_new(&window->btn.b_gpu, &window->win, "GPU MODE", 200, 550);
	kiss_button_new(&window->btn.b_network, &window->win, "NETWORK", 200, 600);
	kiss_button_new(&window->btn.b_menu, &window->win, "TO MENU", 200, 800);
	window->win.visible = 1;
	window->layout->server = 0;
	if (window->layout->draw == 0)
	    return ;
	SDL_RenderClear(window->ren);
	kiss_window_draw(&window->win, window->ren);
	kiss_button_draw(&window->btn.b_menu, window->ren);
	kiss_button_draw(&window->btn.b_cpu, window->ren);
	kiss_button_draw(&window->btn.b_gpu, window->ren);
	kiss_button_draw(&window->btn.b_network, window->ren);
	kiss_label_draw(&window->label, window->ren);
	SDL_RenderPresent(window->ren);
	window->layout->draw = 0;
}

void	ft_client_layout(t_window *window)
{
    int textbox_width =  300;

	window->layout->mode = 2;
	kiss_array_new(&window->objects);
	kiss_window_new(&window->win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
	strcpy(window->message, "THIS IS CLIENT MODE\n     CHOOSE IP:");
	kiss_label_new(&window->label, &window->win, window->message, window->win.rect.w / 2 - strlen(window->message) * kiss_textfont.advance / 2, 100);
	kiss_button_new(&window->btn.b_menu, &window->win, "TO MENU", 200, 800);
	kiss_button_new(&window->btn.get_ip, &window->win, "CONNECT", 200, 290);
	kiss_button_new(&window->btn.disconect, &window->win, "LEAVE", 200, 320);
	kiss_entry_new(&window->btn.input, &window->win, 1, window->ip, 100, 240, 300);
	window->win.visible = 1;
	window->layout->client = 0;
	if (window->layout->draw == 0)
		return ;
	SDL_RenderClear(window->ren);
	kiss_window_draw(&window->win, window->ren);
	kiss_label_draw(&window->label, window->ren);
	kiss_button_draw(&window->btn.b_menu, window->ren);
	kiss_button_draw(&window->btn.disconect, window->ren);
	kiss_entry_draw(&window->btn.input, window->ren);
	kiss_button_draw(&window->btn.get_ip, window->ren);
	SDL_RenderPresent(window->ren);
	window->layout->draw = 0;
}


void    ft_gpu_cpu_layout(t_window *window)
{
	window->layout->mode = 6;
	window->layout->cpu = 0;
	window->layout->gpu = 0;
    int textbox_width =  300;
	kiss_array_new(&window->objects);
	kiss_window_new(&window->win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
	strcpy(window->message, "THIS IS CLIENT MODE\n     CHOOSE FILE PATH:");
	kiss_label_new(&window->label, &window->win, window->message, window->win.rect.w / 2 - strlen(window->message) * kiss_textfont.advance / 2, 100);
	kiss_button_new(&window->btn.b_menu, &window->win, "TO MENU", 200, 800);
	kiss_button_new(&window->btn.upload, &window->win, "UPLOAD", 200, 290);
	kiss_entry_new(&window->btn.input, &window->win, 1, window->ip, 100, 240, 300);
	window->win.visible = 1;
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


void    ft_network_layout(t_window *window)
{
	window->layout->mode = 6;
	window->layout->network = 0;
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


// void    ft_gpu_cpu_layout(t_window *window)
// {
// 	kiss_array_new(&window->objects);
// 	kiss_window_new(&window->win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
// 	strcpy(window->message, "THIS IS CPU/GPU");
// 	kiss_label_new(&window->label, &window->win, window->message, window->win.rect.w / 2 - strlen(window->message) * kiss_textfont.advance / 2, 100);
// 	kiss_button_new(&window->btn.open_file, &window->win, "OPEN F\\", 200, 400);
// 	kiss_button_new(&window->btn.b_menu, &window->win, "TO MENU", 200, 800);
// 	kiss_button_new(&window->btn.b_server, &window->win, "BACK", 200, 830);
// 	window->layout->cpu = 0;
// 	window->layout->gpu = 0;
// 	window->layout->mode = 4;
// 	window->win.visible = 1;
// 	if (window->layout->draw == 0)
// 	    return ;
// 	SDL_RenderClear(window->ren);
// 	kiss_window_draw(&window->win, window->ren);
// 	kiss_button_draw(&window->btn.open_file, window->ren);
// 	kiss_button_draw(&window->btn.b_menu, window->ren);
// 	kiss_button_draw(&window->btn.b_server, window->ren);
// 	kiss_label_draw(&window->label, window->ren);
// 	SDL_RenderPresent(window->ren);
// 	window->layout->draw = 0;
// }

// void    ft_network_layout(t_window *window)
// {
// 	kiss_array_new(&window->objects);
// 	kiss_window_new(&window->win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
// 	strcpy(window->message, "THIS IS NETWORK MODE");
// 	kiss_label_new(&window->label, &window->win, window->message, window->win.rect.w / 2 - strlen(window->message) * kiss_textfont.advance / 2, 100);
// 	kiss_button_new(&window->btn.b_menu, &window->win, "TO MENU", 200, 800);
// 	kiss_button_new(&window->btn.open_file, &window->win, "OPEN F\\", 200, 400);
// 	kiss_button_new(&window->btn.b_server, &window->win, "BACK", 200, 830);
// 	window->layout->mode = 5;
// 	window->layout->network = 0;
// 	window->win.visible = 1;
// 	if (window->layout->draw == 0)
// 	    return ;
// 	SDL_RenderClear(window->ren);
// 	kiss_window_draw(&window->win, window->ren);
// 	kiss_button_draw(&window->btn.open_file, window->ren);
// 	kiss_button_draw(&window->btn.b_menu, window->ren);
// 	kiss_button_draw(&window->btn.b_server, window->ren);
// 	kiss_label_draw(&window->label, window->ren);
// 	SDL_RenderPresent(window->ren);
// 	window->layout->draw = 0;
// }