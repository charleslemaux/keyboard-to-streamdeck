#include "../includes/gl.h"

static Options opts = {0};

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
        case sfKeyNumpad4:
            create_kb_thread();
            break;
    }
    if (key_code >= 75 && key_code <= 84)
        set_title(opts.window, opts.scene);
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

int main(int argc, char **argv)
{
    if (geteuid() != 0) {
        char sudo[]="/usr/bin/sudo";
        char pbin[]="./gl";
        execl(sudo,sudo,pbin,(char *)NULL);
    }
    KeyboardArray kb_array = get_keyboards();
    read_keyboards(&kb_array);

    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = VK_NULL_HANDLE;
    sfEvent event;

    window = sfRenderWindow_create(mode, "OpenGL x CSFML", sfResize | sfClose, NULL);
    if (!window) {
        exit(EXIT_FAILURE);
    }
    opts.window = window;

    pthread_t thread_id = create_kb_thread();

    init_menu_ui();
    while (sfRenderWindow_isOpen(window)) {
        event_handler(window, &event);
        window_manager(window, &kb_array);
        usleep(20000); // 20ms
    }

    pthread_join(thread_id, NULL);
    sfRenderWindow_destroy(window);
    free_keyboards_array(&kb_array);
    exit(EXIT_SUCCESS);
}
