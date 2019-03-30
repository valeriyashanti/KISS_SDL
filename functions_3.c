/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 16:25:05 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/30 20:08:09 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void button_event_cpu(kiss_button *button, SDL_Event *e, int *draw, int *cpu)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("я в режиме ЦПУ хозяин!\n");
		*cpu = 1;
		*draw = 1;
	}
}

void button_event_network(kiss_button *button, SDL_Event *e, int *draw, int *network)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("я в режиме Нетворкинга хозяин!\n");
		*network = 1;
		*draw = 1;
	}
}

char  *button_event_upload(kiss_button *button, SDL_Event *e, int *draw, char *ip)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("Готов загружать сцену!\n");
		printf("%s\n", ip);
	}
	return (ip);
}
