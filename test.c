#include "ui.h"

// ПИЗДЕЦ

static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar)
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
static void dirent_read(kiss_textbox *textbox1, kiss_vscrollbar *vscrollbar1,
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
#ifdef _MSC_VER
	dir = kiss_opendir("*");
#else
	dir = kiss_opendir(".");
#endif
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
static void textbox1_event(kiss_textbox *textbox, SDL_Event *e,
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

static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
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

static void textbox2_event(kiss_textbox *textbox, SDL_Event *e,
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

static void vscrollbar2_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
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

static void button_ok1_event(kiss_button *button, SDL_Event *e,
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

static void button_cancel_event(kiss_button *button, SDL_Event *e,
	int *quit, int *draw)
{
	if (kiss_button_event(button, e, draw)) *quit = 1;
}

static void button_ok2_event(kiss_button *button, SDL_Event *e,
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


// КОНЕЦ ЕГО 

int main()
{
	SDL_Renderer *ren;
	SDL_Event e;
	kiss_array objects;
	kiss_window win;
	kiss_label label = {0};
	kiss_button button = {0};
	kiss_button button1 = {0};
	ren = kiss_init(" -- RT -- ", &objects, 600, 1000);
	if (!ren)
		return (1);
	char message[KISS_MAX_LENGTH];
	int draw;
	int quit;

	// ПИЗДЕЦ

	kiss_array a1, a2;
	kiss_window window2;
	kiss_label label1 = {0}, label2 = {0}, label_sel = {0},
		label_res = {0};
	kiss_button button_ok1 = {0}, button_ok2 = {0}, button_cancel = {0};
	kiss_textbox textbox1 = {0}, textbox2 = {0};
	kiss_vscrollbar vscrollbar1 = {0}, vscrollbar2 = {0};
	kiss_progressbar progressbar = {0};
	kiss_entry entry = {0};
	int textbox_width, textbox_height, window2_width, window2_height;

	textbox_width =  300;
	textbox_height = 250;
	window2_width = 800;
	window2_height = 168;

	kiss_array_new(&a1);
	kiss_array_append(&objects, ARRAY_TYPE, &a1);
	kiss_array_new(&a2);
	kiss_array_append(&objects, ARRAY_TYPE, &a2);

	/* Arrange the widgets nicely relative to each other */

	kiss_textbox_new(&textbox1, &win, 1, &a1, 100, 100, 300, 300);
	kiss_vscrollbar_new(&vscrollbar1, &win, textbox1.rect.x +
		textbox_width, 100, textbox_height);
	kiss_textbox_new(&textbox2, &win, 1, &a2,
		100, 450,
		300, 300);
	kiss_vscrollbar_new(&vscrollbar2, &win, textbox2.rect.x +
		textbox_width, 450, textbox_height);
	kiss_label_new(&label1, &win, "Folders", 100, 430);
	kiss_label_new(&label2, &win, "Files", textbox2.rect.x +
		kiss_edge, textbox1.rect.y - kiss_textfont.lineheight);
	kiss_label_new(&label_sel, &win, "", textbox1.rect.x +
		kiss_edge, textbox1.rect.y + textbox_height +
		kiss_normal.h + 30);
	kiss_entry_new(&entry, &win, 1, "kiss", 100, 750, 300);
	kiss_button_new(&button_cancel, &win, "QUIT",
		280,
		entry.rect.y + entry.rect.h + kiss_normal.h);
	kiss_button_new(&button_ok1, &win, "RENDER", 100, button_cancel.rect.y);
	kiss_window_new(&window2, NULL, 1, 1 , kiss_screen_height / 2 -
		window2_height / 2, 400, window2_height);
	kiss_label_new(&label_res, &window2, "", window2.rect.x +
		kiss_up.w, window2.rect.y + kiss_vslider.h);
	label_res.textcolor = kiss_blue;
	kiss_progressbar_new(&progressbar, &window2, window2.rect.x +
		kiss_up.w - kiss_edge, window2.rect.y + window2.rect.h / 2 -
		kiss_bar.h / 2 - kiss_border,
		window2.rect.w - 2 * kiss_up.w + 2 * kiss_edge);
	kiss_button_new(&button_ok2, &window2, "OK", window2.rect.x +
		window2.rect.w / 2 - kiss_normal.w / 2,
		progressbar.rect.y + progressbar.rect.h +
		2 * kiss_vslider.h);
	dirent_read(&textbox1, &vscrollbar1, &textbox2, &vscrollbar2,
		&label_sel);
	// КОННЕЦ

	int server = 0;
	int client = 0;
	int onstart = 1;
	int cpu = 0;
	int gpu = 0;
	int open = 0;
	int network = 0;
	quit = 0;
	draw = 1;
	kiss_button get_ip = {0};
	kiss_button ex = {0};
	kiss_button menu = {0};
	kiss_button b_cpu = {0};
	kiss_entry input = {0};
	char *ip;
	ip = "e2r4p6";
	kiss_button b_gpu = {0};
	kiss_button disconect = {0};
	kiss_button b_network = {0};
	kiss_button r_button = {0};
	kiss_button start_shit = {0};
	kiss_button open_file = {0};
	label.textcolor.b = 255;
	int mode = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = 1;
			}
			kiss_window_event(&win, &e, &draw);
			if (mode == 1)
			{
				button_event_render(&r_button, &e, &draw);
				button_event_tomenu(&menu, &e, &draw, &onstart, &mode);
				button_event_cpu(&b_cpu, &e, &draw, &cpu);
				button_event_gpu(&b_gpu, &e, &draw, &gpu);
				button_event_network(&b_network, &e, &draw, &network);
			}
			if (mode == 2)
			{
				button_event_connect(&get_ip, &e, &draw, input.text);
				button_event_tomenu(&menu, &e, &draw, &onstart, &mode);
				button_event_disconnect(&disconect, &e, &draw);
 				kiss_entry_event(&input, &e, &draw);
        		if (!draw) continue;
				SDL_RenderClear(ren);
				kiss_window_draw(&win, ren);
				kiss_label_draw(&label, ren);
				kiss_button_draw(&get_ip, ren);
				kiss_button_draw(&disconect, ren);
				kiss_entry_draw(&input, ren);
				kiss_button_draw(&menu, ren);
				SDL_RenderPresent(ren);
			}
			if (mode == 0)
			{
				button_event_client(&button, &e, &draw, &client, &onstart);
				button_event_server(&button1, &e, &draw, &server, &onstart);
			}
			if (mode == 4)
			{
				button_event_tomenu(&menu, &e, &draw, &onstart, &mode);
				button_event_open_f(&open_file, &e, &draw, &mode, &open);
				button_event_server(&button1, &e, &draw, &server, &onstart);
			}
			if (mode == 5)
			{
				button_event_open_f(&open_file, &e, &draw, &mode, &open);
				button_event_tomenu(&menu, &e, &draw, &onstart, &mode);
				button_event_server(&button1, &e, &draw, &server, &onstart);
			}

			if (mode == 6)
			{
				kiss_window_event(&window2, &e, &draw);
				kiss_window_event(&win, &e, &draw);
				textbox1_event(&textbox1, &e, &vscrollbar1,
					&textbox2, &vscrollbar2, &label_sel, &draw);
				vscrollbar1_event(&vscrollbar1, &e, &textbox1,
					&draw);
				textbox2_event(&textbox2, &e, &vscrollbar2, &entry,
					&draw);
				vscrollbar2_event(&vscrollbar2, &e, &textbox2, &draw);
				button_ok1_event(&button_ok1, &e, &win, &window2,
					&label_sel, &entry, &label_res,	&progressbar,
					&draw);
				button_cancel_event(&button_cancel, &e, &quit,
					&draw);
				kiss_entry_event(&entry, &e, &draw);
				button_ok2_event(&button_ok2, &e, &win, &window2,
					&progressbar, &draw);
				button_event_tomenu(&menu, &e, &draw, &onstart, &mode);
				if (!draw)
					continue;
				SDL_RenderClear(ren);
				kiss_window_draw(&win, ren);
				kiss_label_draw(&label1, ren);
				kiss_label_draw(&label2, ren);
				kiss_textbox_draw(&textbox1, ren);
				kiss_vscrollbar_draw(&vscrollbar1, ren);
				kiss_textbox_draw(&textbox2, ren);
				kiss_vscrollbar_draw(&vscrollbar2, ren);
				kiss_label_draw(&label_sel, ren);
				kiss_entry_draw(&entry, ren);
				kiss_button_draw(&menu, ren);
				kiss_button_draw(&button_ok1, ren);
				kiss_button_draw(&button_cancel, ren);
				kiss_window_draw(&window2, ren);
				kiss_label_draw(&label_res, ren);
				kiss_progressbar_draw(&progressbar, ren);
				kiss_button_draw(&button_ok2, ren);
				SDL_RenderPresent(ren);
				int flag;
				if (strlen(label_res.text) && flag != 5)
				{
					SDL_Window *new_w;
					new_w = SDL_CreateWindow("win", 0, 0, 500, 500, 0);
					SDL_Surface *image;
					SDL_Surface *win_surface;
					win_surface = SDL_GetWindowSurface(new_w);
					image = SDL_LoadBMP(label_res.text);
					SDL_BlitSurface(image, NULL, win_surface, NULL);
					SDL_UpdateWindowSurface(new_w);
					printf("%s\n\n\n", label_res.text);
					flag = 5;
				}
			}
		}

		if (onstart == 1)
		{
			kiss_array_new(&objects);
			kiss_window_new(&win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
			strcpy(message, "СHOOSE YOUR MODE");
			kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, 100);
			kiss_button_new(&button, &win, "CLIENT", 200, 750);
			kiss_button_new(&button1, &win, "SERVER", 200, 800);
			onstart = 0;
			win.visible = 1;
				if (!draw)
			continue;
			SDL_RenderClear(ren);
			kiss_window_draw(&win, ren);
			kiss_button_draw(&button, ren);
			kiss_button_draw(&button1, ren);	
			kiss_label_draw(&label, ren);
			SDL_RenderPresent(ren);
			mode = 0;
			draw = 0;
		}
		if (client == 1)
		{
			mode = 2;
			kiss_array_new(&objects);
			kiss_window_new(&win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
			strcpy(message, "THIS IS CLIENT MODE\n     CHOOSE IP:");
			kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, 100);
			kiss_button_new(&menu, &win, "TO MENU", 200, 800);
			kiss_button_new(&get_ip, &win, "CONNECT", 200, 290);
			kiss_button_new(&disconect, &win, "LEAVE", 200, 320);
			kiss_textbox textbox1 = {0};
			kiss_label label1 = {0}, label2 = {0};
			int textbox_width =  300;
			kiss_entry_new(&input, &win, 1, ip, 100, 240, 300);


			win.visible = 1;
			client = 0;
				if (!draw)
			continue;
			SDL_RenderClear(ren);
			kiss_window_draw(&win, ren);
			kiss_label_draw(&label, ren);
			kiss_button_draw(&get_ip, ren);
			kiss_button_draw(&disconect, ren);
			kiss_entry_draw(&input, ren);
			kiss_button_draw(&menu, ren);
			SDL_RenderPresent(ren);
			draw = 0;
		}

		if (server == 1)
		{
			mode = 1;
			kiss_array_new(&objects);
			kiss_window_new(&win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
			strcpy(message, "THIS IS SERVER MODE");
			kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, 100);
			kiss_button_new(&b_cpu, &win, "CPU MODE", 200, 500);
			kiss_button_new(&b_gpu, &win, "GPU MODE", 200, 550);
			kiss_button_new(&b_network, &win, "NETWORK", 200, 600);
			kiss_button_new(&menu, &win, "TO MENU", 200, 800);


			win.visible = 1;
			server = 0;
				if (!draw)
			continue;
			SDL_RenderClear(ren);
			kiss_window_draw(&win, ren);
			kiss_button_draw(&menu, ren);
			kiss_button_draw(&b_cpu, ren);
			kiss_button_draw(&b_gpu, ren);
			kiss_button_draw(&b_network, ren);
			kiss_label_draw(&label, ren);
			SDL_RenderPresent(ren);
			draw = 0;
		}

		if (cpu == 1 || gpu == 1)
		{
			kiss_array_new(&objects);
			kiss_window_new(&win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
			strcpy(message, "THIS IS CPU/GPU");
			kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, 100);
			kiss_button_new(&open_file, &win, "OPEN F\\", 200, 400);
			kiss_button_new(&menu, &win, "TO MENU", 200, 800);
			kiss_button_new(&button1, &win, "BACK", 200, 830);
			cpu = 0;
			gpu = 0;
			mode = 4;
			win.visible = 1;
				if (!draw)
			continue;
			SDL_RenderClear(ren);
			kiss_window_draw(&win, ren);
			kiss_button_draw(&open_file, ren);
			kiss_button_draw(&menu, ren);
			kiss_button_draw(&button1, ren);
			kiss_label_draw(&label, ren);
			SDL_RenderPresent(ren);
			draw = 0;
		}

		if (network == 1)
		{
			kiss_array_new(&objects);
			kiss_window_new(&win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
			strcpy(message, "THIS IS NETWORK MODE");
			kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, 100);
			kiss_button_new(&menu, &win, "TO MENU", 200, 800);
			kiss_button_new(&open_file, &win, "OPEN F\\", 200, 400);
			kiss_button_new(&button1, &win, "BACK", 200, 830);
			mode = 5;
			network = 0;
			win.visible = 1;
				if (!draw)
			continue;
			SDL_RenderClear(ren);
			kiss_window_draw(&win, ren);
			kiss_button_draw(&menu, ren);
			kiss_button_draw(&open_file, ren);
			kiss_button_draw(&button1, ren);
			kiss_label_draw(&label, ren);
			SDL_RenderPresent(ren);
			draw = 0;
		}
		
		if (open == 1)
		{
			vscrollbar1_event(&vscrollbar1, NULL, &textbox1, &draw);
			vscrollbar2_event(&vscrollbar2, NULL, &textbox2, &draw);
			kiss_progressbar_event(&progressbar, NULL, &draw);
			kiss_button_new(&menu, &win, "TO MENU", 200, 850);
			mode = 6;
			if (!draw)
				continue;
			printf("OPENFILE MODE\n");

			SDL_RenderClear(ren);
			kiss_window_draw(&win, ren);
			kiss_label_draw(&label1, ren);
			kiss_label_draw(&label2, ren);
			kiss_textbox_draw(&textbox1, ren);
			kiss_vscrollbar_draw(&vscrollbar1, ren);
			kiss_textbox_draw(&textbox2, ren);
			kiss_vscrollbar_draw(&vscrollbar2, ren);
			kiss_label_draw(&label_sel, ren);
			kiss_entry_draw(&entry, ren);
			kiss_button_draw(&menu, ren);
			kiss_button_draw(&button_ok1, ren);
			kiss_button_draw(&button_cancel, ren);
			kiss_window_draw(&window2, ren);
			kiss_label_draw(&label_res, ren);
			kiss_progressbar_draw(&progressbar, ren);
			kiss_button_draw(&button_ok2, ren);
			SDL_RenderPresent(ren);
			draw = 0;
			int flag;
			if (strlen(label_res.text) && flag != 5)
			{
				SDL_Window *new_w;
				new_w = SDL_CreateWindow("win", 0, 0, 500, 500, 0);
				SDL_Surface *image;
				SDL_Surface *win_surface;
				win_surface = SDL_GetWindowSurface(new_w);
				image = SDL_LoadBMP(label_res.text);
				SDL_BlitSurface(image, NULL, win_surface, NULL);
				SDL_UpdateWindowSurface(new_w);
				printf("%s\n\n\n", label_res.text);
				flag = 5;
			}
			open = 0;
		}
	}
	kiss_clean(&objects);
	return (0);
}
