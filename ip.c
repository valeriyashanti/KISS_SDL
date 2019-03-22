#include "kiss_sdl.h"
void button_event(kiss_button *button, SDL_Event *e, int *draw,
int *quit)
{
if (kiss_button_event(button, e, draw)) *quit = 1;
}
int main(int argc, char **argv)
{
	SDL_Renderer *renderer;
	SDL_Event e;
	kiss_array objects;
	kiss_window window;
	kiss_label label = {0};
	kiss_button button = {0};
	char message[KISS_MAX_LENGTH];
	int draw, quit;
	quit = 0;
	draw = 1;
	kiss_array_new(&objects);
	renderer = kiss_init("Hello kiss_sdl", &objects, 320, 120);
	if (!renderer) return 1;
	kiss_window_new(&window, NULL, 0, 0, 0, kiss_screen_width,
	kiss_screen_height);
	strcpy(message, "Введите IP:");
	kiss_label_new(&label, &window, message, 110, 10);
	label.textcolor.r = 255;
	kiss_button_new(&button, &window, "OK", 120, 70);
	window.visible = 1;
	kiss_textbox textbox1 = {0};
	kiss_entry entry = {0};
	kiss_label label1 = {0}, label2 = {0};
	int textbox_width =  300;
	kiss_entry_new(&entry, &window, 1, "e2r10p1", 0, 35, 320);

	while (!quit) {
		SDL_Delay(10);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = 1;
			button_event(&button, &e, &draw, &quit);
			kiss_entry_event(&entry, &e, &draw);
		}
		if (!draw) continue;
		SDL_RenderClear(renderer);
		kiss_window_draw(&window, renderer);
		kiss_label_draw(&label, renderer);
		kiss_button_draw(&button, renderer);
		kiss_entry_draw(&entry, renderer);
		SDL_RenderPresent(renderer);
		draw = 0;
	}
	printf("%s\n", entry.text);
	kiss_clean(&objects);
	return 0;
}
