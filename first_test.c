#include "kiss_sdl.h"

void button_event_server(kiss_button *button, SDL_Event *e,
	int *draw, int *quit, int *server)
{
	if (kiss_button_event(button, e, draw))
	{
		*server = 1;

		printf("new window\n");
	}
}
void button_event_client(kiss_button *button, SDL_Event *e,
	int *draw, int *quit, int *client)
{
	if (kiss_button_event(button, e, draw))
	{
		*client = 1;
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

int main()
{
	SDL_Renderer *ren;
	SDL_Event e;
	kiss_array objects;
	kiss_window win;
	kiss_label label = {0};
	kiss_button button = {0};
	kiss_button button1 = {0};

	char message[KISS_MAX_LENGTH];
	int draw;
	int quit;
	// my code 

	int server = 0;
	int client = 0;
	int start = 1;
	quit = 0;
	draw = 1;
	kiss_button ex = {0};

	kiss_array_new(&objects);
	ren = kiss_init("Hello kiss_sdl", &objects, 500, 500);
	if (!ren)
		return (1);
	kiss_window_new(&win, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
	strcpy(message, "    Выберите способ подключения - ");
	kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, win.rect.h / 2 - (kiss_textfont.fontheight + 2 * kiss_normal.h) / 2);
	label.textcolor.r = 255;
	kiss_button_new(&button, &win, "Client", win.rect.w / 2 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h);
	kiss_button_new(&button1, &win, "Server", win.rect.w / 4 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h);
	win.visible = 1;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = 1;
			}
			kiss_window_event(&win, &e, &draw);
			button_event_client(&button, &e, &draw, &quit, &client);
			button_event_server(&button1, &e, &draw, &quit, &server);
			button_event_quit(&ex, &e, &draw, &quit, &client);
		}

		if (client == 1)
		{
			SDL_Renderer *newren;
			char m[KISS_MAX_LENGTH];
			newren = kiss_init("Хэй это Клиент!!!", &objects, 500, 500);
			SDL_RenderClear(newren);
			kiss_window new;
			kiss_window_new(&new, NULL, 0, 0, 0, 500, 500);
			kiss_button b = {0};
			kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, win.rect.h / 2 - (kiss_textfont.fontheight + 2 * kiss_normal.h) / 2);
			label.textcolor.r = 255;
			kiss_button_new(&ex, &new, "Exit", new.rect.w / 4 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h);
			new.visible = 1;
			kiss_window_draw(&new, newren);
			kiss_button_draw(&ex, newren);
			SDL_RenderPresent(newren);
			kiss_window_event(&new, &e, &draw);
			client = 0;
		}
		if (server == 1)
		{
			SDL_RenderClear(ren);
			strcpy(message, "    Это сервееер ");
			kiss_label_new(&label, &win, message, win.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2, win.rect.h / 2 - (kiss_textfont.fontheight + 2 * kiss_normal.h) / 2);
			label.textcolor.r = 255;
			kiss_button_new(&ex, &win, "Exit", win.rect.w / 4 - kiss_normal.w / 2, label.rect.y + kiss_textfont.fontheight + kiss_normal.h);
			win.visible = 1;
			kiss_window_draw(&win, ren);
			kiss_button_draw(&ex, ren);
			server = 0;
			start = 0;
		}
		if (!draw)
			continue;
		if (start == 1)
		{
		SDL_RenderClear(ren);
		kiss_window_draw(&win, ren);
		kiss_label_draw(&label, ren);
		kiss_button_draw(&button, ren);
		kiss_button_draw(&button1, ren);		
		}
		SDL_RenderPresent(ren);
		draw = 0;
	}
	kiss_clean(&objects);
	return (0);
}