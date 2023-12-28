#include "../includes/gl.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <libevdev/libevdev.h>
#include <libudev.h>

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
    exit(EXIT_SUCCESS);
}

static int get_keyboards() {
    struct udev *udev = udev_new();
    if (!udev) {
        printf("Failed to create udev\n");
        return 1;
    }

    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "input");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    udev_list_entry_foreach(entry, devices) {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);
        const char *devtype = udev_device_get_property_value(dev, "ID_INPUT_KEYBOARD");
        if (devtype != NULL && strcmp(devtype, "1") == 0) {
            printf("Keyboard device: %s\n", udev_device_get_syspath(dev));
            printf("Keyboard name: %s\n", udev_device_get_property_value(dev, "NAME"));
            // Store the keyboard device information as needed
        }
        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    return 0;
}

__attribute__((constructor)) void init()
{
    get_keyboards();
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
}
