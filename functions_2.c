/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 16:24:09 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/23 16:28:50 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void button_event_server(kiss_button *button, SDL_Event *e, int *draw,  int *server, int *onstart)
{
	if (kiss_button_event(button, e, draw))
	{
		*server = 1;
		*onstart = 0;
		*draw = 1;
		printf("я в режиме сервера хозяин\n");
	}
}

void button_event_client(kiss_button *button, SDL_Event *e, int *draw,int *client, int *onstart)
{
	if (kiss_button_event(button, e, draw))
	{
		*client = 1;
		*onstart = 0;
		*draw = 1;
		printf("я в режиме клиента хозяин\n");
	}
}

void button_event_quit(kiss_button *button, SDL_Event *e, int *draw, int *quit, int *newwindow)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("quit\n");
		*quit = 1;
	}
	
}
void button_event_tomenu(kiss_button *button, SDL_Event *e, int *draw, int *onstart, int *mode)
{
	if (kiss_button_event(button, e, draw))
	{
		*mode = 0;
		printf("я перешел в меню хозяин\n");
		*onstart = 1;
		*draw = 1;
	}
	
}
void button_event_calculate(kiss_button *button, SDL_Event *e, int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("я готов все считать\n");
	}
	
}
