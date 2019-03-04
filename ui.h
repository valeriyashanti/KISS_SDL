/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 11:06:12 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/04 11:09:42 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "kiss_sdl.h"

void button_event_server(kiss_button *button, SDL_Event *e, int *draw,  int *server, int *onstart);
void button_event_client(kiss_button *button, SDL_Event *e, int *draw,int *client, int *onstart);
void button_event_quit(kiss_button *button, SDL_Event *e, int *draw, int *quit, int *newwindow);
void button_event_tomenu(kiss_button *button, SDL_Event *e,int *draw, int *onstart, int *mode);
void button_event_calculate(kiss_button *button, SDL_Event *e, int *draw);
void button_event_connect(kiss_button *button, SDL_Event *e, int *draw, char *ip);
void button_event_disconnect(kiss_button *button, SDL_Event *e, int *draw);
void button_event_render(kiss_button *button, SDL_Event *e, int *draw);
void button_event_gpu(kiss_button *button, SDL_Event *e, int *draw, int *gpu);
void button_event_open_f(kiss_button *button, SDL_Event *e, int *draw, int *mode, int *open);
void button_event_cpu(kiss_button *button, SDL_Event *e, int *draw, int *cpu);
void button_event_network(kiss_button *button, SDL_Event *e, int *draw, int *network);

#endif