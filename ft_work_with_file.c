/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_with_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:49:00 by gkessler          #+#    #+#             */
/*   Updated: 2019/03/30 18:35:16 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar)
{
	qsort(textbox->array->data, textbox->array->length, sizeof(void *),
		kiss_string_compare);
	vscrollbar->step = 0.;
	if (textbox->array->length - textbox->maxlines > 0)
		vscrollbar->step = 1. / (textbox->array->length -
			textbox->maxlines);
	textbox->firstline = 0;
	textbox->highlightline = -1;
	vscrollbar->fraction = 0.;
}

/* Read directory entries into the textboxes */
void dirent_read(kiss_textbox *textbox1, kiss_vscrollbar *vscrollbar1,
	kiss_textbox *textbox2,	kiss_vscrollbar *vscrollbar2,
	kiss_label *label_sel)
{
	kiss_dirent *ent;
	kiss_stat s;
	kiss_dir *dir;
	char buf[KISS_MAX_LENGTH], ending[2];

	kiss_array_free(textbox1->array);
	kiss_array_free(textbox2->array);
	kiss_array_new(textbox1->array);
	kiss_array_new(textbox2->array);
	kiss_getcwd(buf, KISS_MAX_LENGTH);
	strcpy(ending, "/");
	if (buf[0] == 'C') strcpy(ending, "\\");
	if (!strcmp(buf, "/") || !strcmp(buf, "C:\\")) strcpy(ending, "");
	kiss_string_copy(label_sel->text, (2 * textbox1->rect.w +
		2 * kiss_up.w) / kiss_textfont.advance, buf, ending);
	dir = kiss_opendir(".");
	while ((ent = kiss_readdir(dir))) {
		kiss_getstat(ent->d_name, &s);
		if (kiss_isdir(s))
			kiss_array_appendstring(textbox1->array, 0,
				ent->d_name, "/");
		else if (kiss_isreg(s))
			kiss_array_appendstring(textbox2->array, 0,
				ent->d_name, NULL);
	}
	kiss_closedir(dir);
	text_reset(textbox1, vscrollbar1);
	text_reset(textbox2, vscrollbar2);
}

/* The widget arguments are widgets that this widget talks with */
void textbox1_event(kiss_textbox *textbox, SDL_Event *e,
	kiss_vscrollbar *vscrollbar1, kiss_textbox *textbox2,
	kiss_vscrollbar *vscrollbar2, kiss_label *label_sel, int *draw)
{
	int index;

	if (kiss_textbox_event(textbox, e, draw)) {
		index = textbox->firstline + textbox->selectedline;
		if (strcmp((char *) kiss_array_data(textbox->array, index),
			"")) {
			textbox->selectedline = -1;
			kiss_chdir((char *) kiss_array_data(textbox->array,
				index));
			dirent_read(textbox, vscrollbar1, textbox2,
				vscrollbar2, label_sel);
			*draw = 1;
		}
	}
}

void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
	kiss_textbox *textbox1, int *draw)
{
	int firstline;

	if (kiss_vscrollbar_event(vscrollbar, e, draw) &&
		textbox1->array->length - textbox1->maxlines > 0) {
		firstline = (int) ((textbox1->array->length - 
			textbox1->maxlines) * vscrollbar->fraction + 0.5);
		if (firstline >= 0) textbox1->firstline = firstline;
		*draw = 1;
	}
}

void textbox2_event(kiss_textbox *textbox, SDL_Event *e,
	kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw)
{
	int index;

	if (kiss_textbox_event(textbox, e, draw)) {
		index = textbox->firstline + textbox->selectedline;
		if (strcmp((char *) kiss_array_data(textbox->array, index),
			"")) {
			kiss_string_copy(entry->text,
				entry->textwidth / kiss_textfont.advance,
				(char *) kiss_array_data(textbox->array,
				index), NULL);
			*draw = 1;
		}
	}
}

void vscrollbar2_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
	kiss_textbox *textbox2, int *draw)
{
	int firstline;

	if (kiss_vscrollbar_event(vscrollbar, e, draw) &&
		textbox2->array->length) {
		firstline = (int) ((textbox2->array->length - 
			textbox2->maxlines) * vscrollbar->fraction + 0.5);
		if (firstline >= 0) textbox2->firstline = firstline;
		*draw = 1;
	}
}

void button_ok1_event(kiss_button *button, SDL_Event *e,
	kiss_window *window1, kiss_window *window2, kiss_label *label_sel,
	kiss_entry *entry, kiss_label *label_res,
	kiss_progressbar *progressbar, int *draw)
{
	char buf[KISS_MAX_LENGTH];

	if (kiss_button_event(button, e, draw)) {
		kiss_string_copy(buf, kiss_maxlength(kiss_textfont,
			window2->rect.w - 2 * kiss_vslider.w,
			label_sel->text, entry->text),
			label_sel->text, entry->text);
		kiss_string_copy(label_res->text, KISS_MAX_LABEL, 
			"", buf);
		window2->visible = 1;
		window2->focus = 1;
		window1->focus = 0;
		button->prelight = 0;
		progressbar->fraction = 0.;
		progressbar->run = 1;
		*draw = 1;
	}
}

void button_cancel_event(kiss_button *button, SDL_Event *e,
	int *quit, int *draw)
{
	if (kiss_button_event(button, e, draw)) *quit = 1;
}

void button_ok2_event(kiss_button *button, SDL_Event *e,
	kiss_window *window1, kiss_window *window2,
	kiss_progressbar *progressbar, int *draw)
{
	if (kiss_button_event(button, e, draw)) {
		window2->visible = 0;
		window1->focus = 1;
		button->prelight = 0;
		progressbar->fraction = 0.;
		progressbar->run = 0;
		*draw = 1;
	}
}








// 			if (window->mode == 6)
// 			{
// 				
// 			}





		// if (window->open == 1)
		// {
		// 	vscrollbar1_event(&vscrollbar1, NULL, &textbox1, &draw);
		// 	vscrollbar2_event(&vscrollbar2, NULL, &textbox2, &draw);
		// 	kiss_progressbar_event(&progressbar, NULL, &draw);
		// 	kiss_button_new(&menu, &win, "TO MENU", 200, 850);
		// 	window->mode = 6;
		// 	if (!window->draw)
		// 		continue;
		// 	printf("OPENFILE MODE\n");

		// 	SDL_RenderClear(ren);
		// 	kiss_window_draw(&win, ren);
		// 	kiss_label_draw(&label1, ren);
		// 	kiss_label_draw(&label2, ren);
		// 	kiss_textbox_draw(&textbox1, ren);
		// 	kiss_vscrollbar_draw(&vscrollbar1, ren);
		// 	kiss_textbox_draw(&textbox2, ren);
		// 	kiss_vscrollbar_draw(&vscrollbar2, ren);
		// 	kiss_label_draw(&label_sel, ren);
		// 	kiss_entry_draw(&entry, ren);
		// 	kiss_button_draw(&menu, ren);
		// 	kiss_button_draw(&button_ok1, ren);
		// 	kiss_button_draw(&button_cancel, ren);
		// 	kiss_window_draw(&window2, ren);
		// 	kiss_label_draw(&label_res, ren);
		// 	kiss_progressbar_draw(&progressbar, ren);
		// 	kiss_button_draw(&button_ok2, ren);
		// 	SDL_RenderPresent(ren);
		// 	window->draw = 0;
		// 	int flag;
		// 	if (strlen(label_res.text) && flag != 5)
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
		// 		flag = 5;
		// 	}
		// 	window->open = 0;
		// }		// if (window->open == 1)
		// {
		// 	vscrollbar1_event(&vscrollbar1, NULL, &textbox1, &draw);
		// 	vscrollbar2_event(&vscrollbar2, NULL, &textbox2, &draw);
		// 	kiss_progressbar_event(&progressbar, NULL, &draw);
		// 	kiss_button_new(&menu, &win, "TO MENU", 200, 850);
		// 	window->mode = 6;
		// 	if (!window->draw)
		// 		continue;
		// 	printf("OPENFILE MODE\n");

		// 	SDL_RenderClear(ren);
		// 	kiss_window_draw(&win, ren);
		// 	kiss_label_draw(&label1, ren);
		// 	kiss_label_draw(&label2, ren);
		// 	kiss_textbox_draw(&textbox1, ren);
		// 	kiss_vscrollbar_draw(&vscrollbar1, ren);
		// 	kiss_textbox_draw(&textbox2, ren);
		// 	kiss_vscrollbar_draw(&vscrollbar2, ren);
		// 	kiss_label_draw(&label_sel, ren);
		// 	kiss_entry_draw(&entry, ren);
		// 	kiss_button_draw(&menu, ren);
		// 	kiss_button_draw(&button_ok1, ren);
		// 	kiss_button_draw(&button_cancel, ren);
		// 	kiss_window_draw(&window2, ren);
		// 	kiss_label_draw(&label_res, ren);
		// 	kiss_progressbar_draw(&progressbar, ren);
		// 	kiss_button_draw(&button_ok2, ren);
		// 	SDL_RenderPresent(ren);
		// 	window->draw = 0;
		// 	int flag;
		// 	if (strlen(label_res.text) && flag != 5)
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
		// 		flag = 5;
		// 	}
		// 	window->open = 0;
		// }







