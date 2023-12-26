#include "../includes/gl.h"
#include <stdlib.h>
#include <stdio.h>

static Options opts;

static void key_handler(sfKeyCode key_code)
{
    opts.key = key_code;
    switch (key_code) {
        case sfKeyNumpad5:
            exit(EXIT_FAILURE);
        case sfKeyNumpad0:
            opts.scene = Menu;
            break;
        case sfKeyNumpad1:
            opts.scene = Sequel;
            break;
        case sfKeyNumpad2:
            opts.scene = MainScreen;
            break;
        case sfKeyNumpad3:
            opts.scene = Ending;
            break;
    }
    if (key_code >= 75 && key_code <= 84)
        set_title(opts.w, opts.scene);
}

static void event_handler(sfRenderWindow* w, sfEvent* e)
{
	if (!sfRenderWindow_pollEvent(w, e))
		return;
	switch (e->type)
	{
        case sfEvtLostFocus:
            break;
        case sfEvtGainedFocus:
            break;
        case sfEvtKeyPressed:
            key_handler(e->key.code);
            break;
		case sfEvtClosed:
			sfRenderWindow_close(w);
			break;
	}
}

int main(int argc, char** argv)
{
	sfVideoMode mode = {800, 600, 32};
	sfRenderWindow *window = VK_NULL_HANDLE;
	sfEvent event;

	window = sfRenderWindow_create(mode, "OpenGL x CSFML", sfResize | sfClose, NULL);
	if (!window)
		exit(EXIT_FAILURE);
    opts.w = window;

	while (sfRenderWindow_isOpen(window)) {
		event_handler(window, &event);
		window_manager(window);
	}
	sfRenderWindow_destroy(window);
    exit(EXIT_SUCCESS);
}
