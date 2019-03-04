
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