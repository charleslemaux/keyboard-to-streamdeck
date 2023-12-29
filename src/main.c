#include "../includes/gl.h"
#include "../includes/keyboards.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>
#include <libevdev/libevdev.h>

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
    int i = 1;
    struct libevdev *dev = NULL;
    int fd;
    int rc;

    fd = open("/dev/input/event3", O_RDONLY|O_NONBLOCK); //TODO : Keyboard listener (from /dev/input/by-id)
    if (fd < 0) {
        perror("Failed to open the input device");
        exit(EXIT_FAILURE);
    }

    rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        perror("Failed to init libevdev");
        close(fd);
        exit(EXIT_FAILURE);
    }

    while(i) {
        struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        if (rc == 0 && ev.type == EV_KEY && ev.value == 1) {
            switch (ev.code) {
                case KEY_SPACE:
                    printf("Spacebar pressed\n");
                    break;
                case KEY_X:
                    printf("X pressed\n");
                    break;
                case KEY_TAB:
                    i = 0;
                    break;
            }
        }
    }
    libevdev_free(dev);
    close(fd);
    printf("\nEXIT_SUCCESS\n");
    exit(EXIT_SUCCESS);
}

__attribute__((constructor)) int init()
{
    if (geteuid() != 0) {
        char sudo[]="/usr/bin/sudo";
        char pbin[]="./gl";
        execl(sudo,sudo,pbin,(char *)NULL);
    }
    KeyboardArray kb_array = get_keyboards();
    read_keyboards(&kb_array);
    free_keyboards_array(&kb_array);

/*	sfVideoMode mode = {800, 600, 32};
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
	sfRenderWindow_destroy(window);*/
    return (1);
}
