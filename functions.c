/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 16:25:26 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/23 16:28:56 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void button_event_connect(kiss_button *button, SDL_Event *e, int *draw, char *ip)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("Готов подключаться хозяин!\n");
		printf("%s\n", ip);
	}
}

void button_event_disconnect(kiss_button *button, SDL_Event *e, int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("Готов отключаться хозяин!\n");
	}
}

void button_event_render(kiss_button *button, SDL_Event *e, int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("я готов все рендерить\n");
	}
}

void button_event_gpu(kiss_button *button, SDL_Event *e, int *draw, int *gpu)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("я в режиме ГПУ хозяин!\n");
		*gpu = 1;
		*draw = 1;
	}
}

void button_event_open_f(kiss_button *button, SDL_Event *e, int *draw, int *mode, int *open)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("я в режиме открывать окно для выбора файла хозяин!\n");
		*mode = 6;
		*open = 1;
		*draw = 1;
	}
}
