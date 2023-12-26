#include "includes/gl.h"
#include <stdlib.h>
#include <stdio.h>

static Options opts;

static void key_handler(sfKeyCode key_code)
{
    opts.key = key_code;
    switch (key_code) {
        case sfKeyNumpad5:
            exit(EXIT_FAILURE);
        case sfKeyNumpad1:
            opts.scene = Menu;
            break;
        case sfKeyNumpad2:
            opts.scene = Sequel;
            break;
        case sfKeyNumpad3:
            opts.scene = MainScreen;
            break;
    }
}

static void event_handler(sfRenderWindow* w, sfEvent* e)
{
	if (!sfRenderWindow_pollEvent(w, e))
		return;
	switch (e->type)
	{
        case sfEvtLostFocus:
            printf("Lost focus\n");
            break;
        case sfEvtGainedFocus:
            printf("Gained focus\n");
            break;
        case sfEvtKeyPressed:
            key_handler(e->key.code);
            break;
		case sfEvtClosed:
			sfRenderWindow_close(w);
			break;
	}
}

static void window_manager(sfRenderWindow* w)
{
    //printf("Scene : %d\nWadress : %p\nKeyCode : %d\n", opts.scene, opts.w, opts.key);
	sfRenderWindow_clear(w, sfWhite);
	sfRenderWindow_display(w);
}

int main(int argc, char** argv)
{
	sfVideoMode mode = {800, 600, 32};
	sfRenderWindow* window;
	sfEvent event;

    opts.w = window;
	window = sfRenderWindow_create(mode, "OpenGL - sim 1", sfResize | sfClose, NULL);
	if (!window)
		return (EXIT_FAILURE);

	while (sfRenderWindow_isOpen(window)) {
		event_handler(window, &event);
		window_manager(window);
	}
	sfRenderWindow_destroy(window);
	return (0);
}
