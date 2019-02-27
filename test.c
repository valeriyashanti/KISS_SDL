#include "kiss_sdl.h"

void button_event_server(kiss_button *button, SDL_Event *e,
	int *draw,  int *server, int *onstart)
{
	if (kiss_button_event(button, e, draw))
	{
		*server = 1;
		*onstart = 0;
		*draw = 1;
		printf("new window\n");
	}
}
void button_event_client(kiss_button *button, SDL_Event *e,
	int *draw,int *client, int *onstart)
{
	if (kiss_button_event(button, e, draw))
	{
		*client = 1;
		*onstart = 0;
		*draw = 1;
		printf("new window\n");
	}
}

void button_event_quit(kiss_button *button, SDL_Event *e,
	int *draw, int *quit, int *newwindow)
{
	if (kiss_button_event(button, e, draw))
	{
		// *newwindow = 1;
		printf("quit\n");
		*quit = 1;
	}
	
}
void button_event_tomenu(kiss_button *button, SDL_Event *e,
	int *draw, int *onstart)
{
	if (kiss_button_event(button, e, draw))
	{
		// *newwindow = 1;
		printf("to menu\n");
		*onstart = 1;
	}
	
}
void button_event_calculate(kiss_button *button, SDL_Event *e,
	int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		// *newwindow = 1;
		printf("я готов все считать\n");
	}
	
}
void button_event_render(kiss_button *button, SDL_Event *e,
	int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		// *newwindow = 1;
		printf("я готов все рендерить\n\n");
	}
}

int main()
{
	SDL_Renderer *ren;
	SDL_Event e;
	kiss_array objects;
	kiss_window win;
	kiss_label label = {0};
	kiss_button button = {0};
	kiss_button button1 = {0};
	ren = kiss_init("Hello kiss_sdl", &objects, 500, 500);
	if (!ren)
		return (1);
	char message[KISS_MAX_LENGTH];
	int draw;
	int quit;
	// my code 

	int server = 0;
	int client = 0;
	int onstart = 1;
	quit = 0;
	draw = 1;
	kiss_button ex = {0};
	kiss_button menu = {0};
	kiss_button r_button = {0};
	kiss_button start_shit = {0};
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
				button_event_tomenu(&menu, &e, &draw, &onstart);
			}
			if (mode == 2)
			{
				button_event_calculate(&start_shit, &e, &draw);
				button_event_tomenu(&menu, &e, &draw, &onstart);
			}
			if (mode == 0)
			{
				button_event_client(&button, &e, &draw, &client, &onstart);
				button_event_server(&button1, &e, &draw, &server, &onstart);
			}
			// button_event_quit(&ex, &e, &draw, &quit, &client);
			// button_event_render(&r_button, &e, &draw);
		}
		if (onstart == 1)
		{
			kiss_array_new(&objects);
			kiss_window_new(&win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
			strcpy(message, "    Выберите способ подключения - ");
			kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, win.rect.h / 2 - (kiss_textfont.fontheight + 2 * kiss_normal.h) / 2);
			label.textcolor.r = 255;
			kiss_button_new(&button, &win, "Client", win.rect.w / 2 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h / 2);
			kiss_button_new(&button1, &win, "Server", win.rect.w / 4 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h / 2);
			win.visible = 1;

			// menu.active = 0;
			onstart = 0;
				if (!draw)
			continue;
			SDL_RenderClear(ren);
			kiss_window_draw(&win, ren);
			kiss_button_draw(&button, ren);
			kiss_button_draw(&button1, ren);	
			kiss_label_draw(&label, ren);
			// kiss_button_draw(&button1, ren);		
			SDL_RenderPresent(ren);
			mode = 0;
			draw = 0;
		}
		if (client == 1)
		{
			kiss_array_new(&objects);
			kiss_window_new(&win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
			strcpy(message, "   Это клиент");
			kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, win.rect.h / 2 - (kiss_textfont.fontheight + 2 * kiss_normal.h) / 2);
			label.textcolor.r = 255;
			// kiss_button_new(&ex, &win, "Exit", win.rect.w / 2 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h);
			kiss_button_new(&menu, &win, "To Menu", win.rect.w / 4 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h * 2);
			kiss_button_new(&start_shit, &win, "Start Shit", win.rect.w / 1.5 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h * 2);
			// menu.active = 0;
			mode = 2;
			win.visible = 1;
			client = 0;
			// SDL_RenderClear(ren);
				if (!draw)
			continue;
			SDL_RenderClear(ren);
			kiss_window_draw(&win, ren);
			// kiss_button_draw(&ex, ren);
			kiss_label_draw(&label, ren);
			kiss_button_draw(&start_shit, ren);
			kiss_button_draw(&menu, ren);
			// kiss_button_draw(&button1, ren);		
			SDL_RenderPresent(ren);
			draw = 0;
			// kiss_window_draw(&win, ren);
		}
		if (server == 1)
		{
			mode = 1;
			kiss_array_new(&objects);
			kiss_window_new(&win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
			strcpy(message, " Это сервер");
			kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, win.rect.h / 2 - (kiss_textfont.fontheight + 2 * kiss_normal.h) / 2);
			label.textcolor.r = 255;
			// kiss_button_new(&ex, &win, "Exit", win.rect.w / 2 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h);
			kiss_button_new(&r_button, &win, "Render", win.rect.w / 1.5 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h);
			kiss_button_new(&menu, &win, "To Menu", win.rect.w / 3 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h);
			win.visible = 1;
						printf("button r_button = %d\n", r_button.active);

			server = 0;
				if (!draw)
			continue;
			SDL_RenderClear(ren);
			kiss_window_draw(&win, ren);
			// kiss_button_draw(&ex, ren);
			kiss_button_draw(&r_button, ren);
			kiss_button_draw(&menu, ren);
			kiss_label_draw(&label, ren);
			// kiss_button_draw(&button1, ren);		
			SDL_RenderPresent(ren);
			draw = 0;
			// SDL_RenderClear(ren);
			// kiss_window_draw(&win, ren);
		}

	}
	kiss_clean(&objects);
	return (0);
}